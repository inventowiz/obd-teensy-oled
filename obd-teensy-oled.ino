#ifndef __IMXRT1062__
  #error "This sketch should be compiled for Teensy 4.0"
#endif

#define DELAYS

//#include <Watchdog_t4.h>
#include <malloc.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <U8g2lib.h>

#include <FlexCAN_T4.h>
#define VEH_CAN_SPEED 500000
#define VEH_CAN_DEVICE CAN1
#define RAD_CAN_SPEED 500000
#define RAD_CAN_DEVICE CAN2

// autogenerated C code from python-cantools
#include "subaru_hscan.h"
#include "mrr_pcan.h"

// scratch space for CAN data
CAN_message_t veh_can_message, rad_can_message;
FlexCAN_T4<VEH_CAN_DEVICE, RX_SIZE_256, TX_SIZE_16> veh_can;
FlexCAN_T4<RAD_CAN_DEVICE, RX_SIZE_256, TX_SIZE_16> rad_can;

// Variables for Subaru ECU Kline comms
volatile uint8_t ecu_init_done = false; // flag to ensure we are init'd
static uint8_t const SSM_init_msg[6] = {0x80,0x10,0xf0,0x01,0xbf,0x40};
static uint16_t const SSM_pid_list[] = {0x24, 0x11, 0x2A, 0x2E}; // MAP, Timing, Fuel Temp, Fuel Level V
volatile uint8_t SSM_scratch[sizeof(SSM_pid_list)/sizeof(uint16_t)] = { 0 };
volatile uint8_t SSM_poll_scratch[7+3*(sizeof(SSM_pid_list)/sizeof(uint16_t))] = {0};

#include <TimeLib.h>
#include <TinyGPS.h>

#include <TeensyThreads.h>
volatile uint8_t thread_pids[5] = { 0 }; // threads in this list will trip the WDT
enum { PID_DISPLAY, PID_GPS, PID_VEHCAN, PID_RADCAN, PID_KLINE};

// Timers for firing high precision tasks
IntervalTimer TaskPetWdt;
IntervalTimer CalcNewLongTerms;

//Conversions + constants
#define EARLY_START_MS 2500
#define FUEL_AVG_CYCLES 10
#define MPG_AVG_CYCLES 25
#define FUEL_CAP_GAL 16.9
#define FUEL_RES_FULL 2
#define FUEL_RES_EMPTY 94
#define FT_TO_CM 30.48
#define MI_TO_KM 1.60934
#define C_TO_F(c) ((c*9/5)+32)
#define GAL_TO_MM3 3.785e+6
#define MIN_TO_SEC 60
#define HOUR_TO_SEC 60*60

// Pin definitions
#define OLED_CS     10
#define OLED_DC     19
#define OLED_RESET  18
#define CAN_ENn     2
#define KLINE_EN    3
#define LED5        6
#define LED4        7
#define GPS_PPS     8
#define GPS_RSTn    9
#define GPS_Serial  Serial3
#define Spare_Serial Serial4
#define KLINE_Serial Serial5

// store the last time we displayed on screen
volatile uint32_t loopTimer = millis();

// flag on showing comms diag information
volatile bool flag_debug_kline = false;
volatile bool flag_debug_can = false;
volatile bool flag_debug_info = false;
volatile bool flag_debug_gps = false;

// Display is 256x64 pixels
// Use hardware SPI for display (tested up to 110FPS)
U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI oled(U8G2_R2, OLED_CS, OLED_DC, OLED_RESET);
// data divisions
static const uint8_t leftLineX = (oled.getDisplayWidth()/2)-(6*7);
static const uint8_t rightLineX = (oled.getDisplayWidth()/2)+(6*8);
static const uint8_t leftDiv1Y = (oled.getDisplayHeight()/4);
static const uint8_t leftDiv2Y = 2*(oled.getDisplayHeight()/4)+2;
static const uint8_t leftDiv3X = (oled.getDisplayWidth()/4)-16;
static const uint8_t rightDiv1Y = (oled.getDisplayHeight()/4);
static const uint8_t rightDiv2Y = 2*(oled.getDisplayHeight()/4)+2;
static const uint8_t rightDiv3Y = 3*(oled.getDisplayHeight()/4)-2;
static const uint8_t x_ctr = (rightLineX-leftLineX)/2 + leftLineX;

// GPS Module
TinyGPS gps;
// Offset hours from gps time (UTC)
//#define TZ_OFFSET -5  // Eastern Standard Time (USA)
#define TZ_OFFSET -4  // Eastern Daylight Time (USA)

// real time GPS data, only modified in one thread
uint32_t age;
float lat, lon;

// real time vehicle data
struct RT_data {
  float temp_eng, temp_fuel, temp_ext; // degC
  float spd_wheel_fl, spd_wheel_fr, spd_wheel_rl, spd_wheel_rr; // km/h
  float fuel_consumption_inst, fuel_mpg_inst; // mm^3/sec
  float manifold_pressure, timing_advance;
  
  float steering_angle, accel_pos, brake_pos, fuel_res, fuel_v, fuel_percent;
  uint16_t eng_speed, gear_pos, speed_cruise;
  float speed_kph, trans_tq, eng_tq, loss_tq; // kph, Nm
  
  uint8_t brake_sw, compressor_sw, reverse_sw, wiper_sw, 
        bright_sw, headlight_sw, drl_sw, handbrake_sw, clutch_sw,
        mil_sw, cruise_set_sw, cruise_sw, brake_sw1;
} typedef RT_data;
volatile RT_data rtd = {0};

// radar detections data + status
#define NUM_DETECTIONS 64
struct RAD_detection {
  uint8_t is_valid, is_nd, is_super_res, is_clutter;
  float azimuth, range, rate; // deg, m, m/s
  uint8_t amplitude, scan_index; // dbsm
} typedef RAD_detection;
struct RAD_data {
  RAD_detection det[NUM_DETECTIONS];
  // status data
  // TODO
} typedef RAD_data;
volatile RAD_data rad = {0};

// long term vehicle data, use battery backed NVRAM section
// 32 bytes are available, but the last 4 are used by the RTC
// use 0x4003E000 if using teensy 3
//#define NVRAM (uint32_t *)0x400A4000
//uint32_t* NVRAM = new uint32_t(0);
// 2 32 bit Dwords - 3rd next isn't fully writeable and 4th has bit set in high 16 bits and those 16 bits won't change
#define NVRAM ((uint32_t *)0x400A4000)
//volatile uint32_t* miles_to_e = &NVRAM[0]; // 10x
//volatile uint32_t* fuel_mpg_trip = &NVRAM[1]; //5x

// non backed long term data, try to calculate from existing info on start and refine from there
volatile float prev_speed_kph = 0;
volatile float miles_to_e = 0;
volatile float fuel_mpg_trip = 20.0;
volatile float fuel_percent = 100*(miles_to_e/(fuel_mpg_trip*FUEL_CAP_GAL));

void setup() {  
  // USB serial interfaces
  Serial.begin(115200); //console
  pinMode(LED5,OUTPUT);
  Serial1.begin(115200); // GPS + Kline Monitor
  Serial2.begin(115200); // CAN monitor

  // GPS interface & RTC
  GPS_Serial.begin(9600);

  // CAN and KLINE
  pinMode(CAN_ENn,OUTPUT);
  digitalWrite(CAN_ENn,LOW); // turn on CAN tranceiver
  veh_can.begin();
  veh_can.setBaudRate(VEH_CAN_SPEED);
  // set up CAN filters
  veh_can.setFIFOFilter(REJECT_ALL);
  //veh_can.setFIFOFilter(0,SUBARU_HSCAN_STEERING_SENSOR_STATUS_FRAME_ID,STD); // steering sensor status
  veh_can.setFIFOFilterRange(0,SUBARU_HSCAN_ECU_STATUS_1_FRAME_ID,SUBARU_HSCAN_ECU_STATUS_2_FRAME_ID,STD); // ECU status 1,2
  veh_can.setFIFOFilterRange(0,SUBARU_HSCAN_DRIVER_INPUT_FRAME_ID,SUBARU_HSCAN_BODY_STAT_1_FRAME_ID,STD); // Driver input, speed, wheel speeds, body stat 1
  veh_can.setFIFOFilter(0,SUBARU_HSCAN_BODY_STAT_2_FRAME_ID,STD); // body stat 2
  veh_can.enableFIFO();

  rad_can.begin();
  rad_can.setBaudRate(RAD_CAN_SPEED);
  rad_can.setFIFOFilter(REJECT_ALL);
  rad_can.setFIFOFilterRange(0,MRR_PCAN_MRR_DETECTION_001_FRAME_ID,MRR_PCAN_MRR_DETECTION_064_FRAME_ID,STD); // Detections 1-64
  //rad_can.setFIFOFilter(0,MRR_PCAN_MRR_STATUS_RADAR_FRAME_ID,STD); // status
  rad_can.enableFIFO();
  
  // set up kline interface
  pinMode(KLINE_EN,OUTPUT);
  digitalWrite(KLINE_EN,HIGH); // turn on kline tranceiver
  KLINE_Serial.begin(4800);
  

  // Start the OLED and display old buffer
  oled.begin();
  //oled.setRotation(2); //if we need it to be upside down
  oled.clearBuffer();
  oled.setFont(u8g2_font_inb42_mf);
  oled.setFontPosTop();
  oled.setCursor(0,0);
  oled.print("Subaru");
  oled.sendBuffer();

  // Define and start the high precision timers
  TaskPetWdt.begin(petWdt, 500000); // 500ms
  CalcNewLongTerms.begin(calcLongTerms, 1000000); // 1000ms

  // wait a tick before kicking off the threads
  delay(500);

  // Enable a watchdog with a long interval
  noInterrupts();
  //wdt.setTimeout(1);  // seconds
  //wdt.begin();   
  interrupts();

  // Montored threads, default stack size is 1024 bytes
  threads.setSliceMillis(1);
  thread_pids[PID_DISPLAY] = threads.addThread(updateDisplayTask,NULL,13000); // 20 ms cycle time
  thread_pids[PID_GPS] = threads.addThread(processGPSUpdateRTCTask,NULL,2048); // 1000 ms cycle time
  thread_pids[PID_VEHCAN] = threads.addThread(serviceVEHCANTask,NULL,2048); // 10ms cycle time
  thread_pids[PID_RADCAN] = threads.addThread(serviceRADCANTask,NULL,2048); // 10ms cycle time
  thread_pids[PID_KLINE] = threads.addThread(serviceKlineTask,NULL,2048); // 25ms cycle time

  // unmonitored threads
  threads.addThread(serviceUSBSerial,NULL,2048); // 500ms cycle time
  
}

void loop() {
  // using threads
  // do nothing here
}

void serviceUSBSerial(){
  while(1){
    digitalWrite(LED5,!digitalRead(LED5));
    
    String cmd;
    if(Serial.available() ){
      cmd = Serial.readString();
      //Serial.print(cmd.charAt(cmd.length()));
    }
    cmd.trim();
    if(cmd.length() < 3)
      continue;
      
    if(cmd == "relay kline"){ // kline relay through USB
        // suspend the task that is using this interface
        threads.suspend(thread_pids[PID_KLINE]);
        // 10ms cycle time. block until user quits
        threads.wait(threads.addThread(serialUSBRelayTask,(void*)&KLINE_Serial),0);
        threads.restart(thread_pids[PID_KLINE]);
    }else if(cmd == "relay gps"){ // gps relay through USB
        // suspend the task that is using this interface
        threads.suspend(thread_pids[PID_GPS]);
        // 10ms cycle time. block until user quits
        threads.wait(threads.addThread(serialUSBRelayTask,(void*)&GPS_Serial),0);
        threads.restart(thread_pids[PID_GPS]);
    }else if(cmd == "meminfo"){ // print memory info
        Serial.print("                  arena: ");Serial.println(mallinfo().arena);
        Serial.print("  total allocated space: ");Serial.println(mallinfo().uordblks);
        Serial.print("  total non-inuse space: ");Serial.println(mallinfo().fordblks);
        Serial.print("   top releasable space: ");Serial.println(mallinfo().keepcost);
        Serial.println("");
    }else if(cmd == "dbg kline"){ // toggle kline debug
        Serial.println(F("Kline debug messages enabled/disabled"));
        flag_debug_kline = !flag_debug_kline;
    }else if(cmd == "dbg can"){ // toggle can debug
        Serial.println(F("CAN debug messages enabled/disabled"));
        flag_debug_can = !flag_debug_can;
    }else if(cmd == "dbg info"){ // toggle info debug
        Serial.println(F("INFO debug messages enabled/disabled"));
        flag_debug_info = !flag_debug_info;
    }else if(cmd == "dbg gps"){ // toggle gps debug
        Serial.println(F("GPS debug messages enabled/disabled"));
        flag_debug_gps = !flag_debug_gps;
    }else if(cmd == "help"){ // print help text
        Serial.println("relay kline: kline relay");
        Serial.println("relay gps: gps relay");
        Serial.println("meminfo: memory info");
        Serial.println("dbg kline: toggle print kline debug info");
        Serial.println("dbg can: toggle print can debug info");
        Serial.println("dbg gps: toggle print gps debug info");
        Serial.println("dbg info: toggle print real time vehicle debug info");
        Serial.println("help: this help text");
    }else{
      Serial.print(cmd);
      Serial.println(": Invalid command");
    }
    // new line, print prompt
    Serial.print("\n>> ");

    if(flag_debug_info){
      Serial.printf("###################\n");
      Serial.printf("Timestamp:\t%16lu\n",second());
      Serial.printf("Steering angle:\t%d deg\n",rtd.steering_angle);
      Serial.printf("Accel pos:\t%f%%\n",rtd.accel_pos);
      Serial.printf("Brake pos:\t%f%%\n",rtd.brake_pos);
      Serial.printf("Engine speed:\t%d rpm\n",rtd.eng_speed);
      Serial.printf("Vehicle speed:\t%f kph\n",rtd.speed_kph);
      Serial.printf("WSS (kph):\t%f %f\n\t\t%f %f\n",rtd.spd_wheel_fl, rtd.spd_wheel_fr, rtd.spd_wheel_rl, rtd.spd_wheel_rr);
      Serial.printf("Torques (Nm):\tE %f T %f\n\t\tL %f\n",rtd.eng_tq, rtd.trans_tq, rtd.loss_tq);
      Serial.printf("Switches:\tCompressor %d\n\t\tReverse %d\n\t\tBrake %d\n\t\tHandbrake %d\n",rtd.compressor_sw ? 1 : 0, rtd.reverse_sw ? 1 : 0, rtd.brake_sw ? 1 : 0, rtd.handbrake_sw ? 1 : 0);
      Serial.printf("\t\tWiper %d\n\t\tHighBeam %d\n\t\tLowBeam %d\n\t\tDRL %d\n\t\tClutch %d\n",rtd.wiper_sw ? 1 : 0, rtd.bright_sw ? 1 : 0, rtd.headlight_sw ? 1 : 0, rtd.drl_sw ? 1 : 0, rtd.clutch_sw ? 1 : 0);
      Serial.printf("External Temp:\t%f degC\n",rtd.temp_ext);
      Serial.printf("Coolant Temp:\t%f degC\n",rtd.temp_eng);
      Serial.printf("Fuel sensor:\t%f Ohms %f%% %f%%\n",rtd.fuel_res, fuel_percent, rtd.fuel_percent);
      Serial.printf("Fuel consump.:\t%d mm^3/s %f mpg %f mpg/t\n",rtd.fuel_consumption_inst, rtd.fuel_mpg_inst, fuel_mpg_trip);
      Serial.printf("Miles to E:\t%f\n",miles_to_e);
      Serial.printf("###################\n");

    }
    #ifdef DELAYS
    threads.delay(100);
    #endif
  }
}

void serialUSBRelayTask(void *arg){
  // arg must be a hardware serial device
  HardwareSerial *serial = (HardwareSerial*)arg;
  Serial.println(F("Starting serial relay on Serial1, ctrl+c to quit"));
  while(1){
    while(Serial.available()){
      // handle exit seq
      if(Serial.peek() == 0x03){ //ctrl+c
        Serial.println(F("Killing serial relay"));
        return;
      } 
    }
    noInterrupts();  
    while(Serial1.available())
      serial->write(Serial1.read());
    while(serial->available())
      Serial1.write(serial->read());
    interrupts();

    #ifdef DELAYS
    //threads.delay(2);
    #endif
  }
}

void serviceVEHCANTask(){
  while(1){
    // handle CAN message processing here
    
    while(veh_can.read(veh_can_message)){

      if(flag_debug_can){
        Serial.printf(F("Frame received! ID: %03x D:"),veh_can_message.id);
        for(int i=0;i<veh_can_message.len;i++){
          Serial.printf(F(" %02x"),veh_can_message.buf[i]);
        }
        Serial.println("");
      }

      switch(veh_can_message.id){
        case SUBARU_HSCAN_STEERING_SENSOR_STATUS_FRAME_ID:{
          // Steering Sensor Status
          subaru_hscan_steering_sensor_status_t temp;
          subaru_hscan_steering_sensor_status_unpack(&temp,veh_can_message.buf,veh_can_message.len);
        }break;
        case SUBARU_HSCAN_ECU_STATUS_1_FRAME_ID:{
          // ECU Status 1
          subaru_hscan_ecu_status_1_t temp;
          subaru_hscan_ecu_status_1_unpack(&temp,veh_can_message.buf,veh_can_message.len);
          
          rtd.accel_pos = subaru_hscan_ecu_status_1_accel_pos_decode(temp.accel_pos);
          rtd.eng_speed = subaru_hscan_ecu_status_1_engine_speed_decode(temp.engine_speed);
          rtd.trans_tq = subaru_hscan_ecu_status_1_trans_tq_decode(temp.trans_tq);
          rtd.eng_tq = subaru_hscan_ecu_status_1_eng_tq_decode(temp.eng_tq);
          rtd.loss_tq = subaru_hscan_ecu_status_1_loss_tq_decode(temp.loss_tq);
          rtd.compressor_sw = subaru_hscan_ecu_status_1_compressor_sw_decode(temp.compressor_sw);

        }break;
        case SUBARU_HSCAN_ECU_STATUS_2_FRAME_ID:{
          subaru_hscan_ecu_status_2_t temp;
          subaru_hscan_ecu_status_2_unpack(&temp,veh_can_message.buf,veh_can_message.len);
          
          // ECU Status 2
          rtd.gear_pos = subaru_hscan_ecu_status_2_gear_decode(temp.gear);
          rtd.speed_cruise = subaru_hscan_ecu_status_2_cruise_speed_decode(temp.cruise_speed);
          rtd.mil_sw = subaru_hscan_ecu_status_2_mil_sw_decode(temp.mil_sw);
          rtd.cruise_set_sw = subaru_hscan_ecu_status_2_cruise_set_decode(temp.cruise_set);
          rtd.cruise_sw = subaru_hscan_ecu_status_2_cruise_cruise_decode(temp.cruise_cruise);
          rtd.brake_sw1 = subaru_hscan_ecu_status_2_brake_sw_1_decode(temp.brake_sw_1);

        }break;
        case SUBARU_HSCAN_DRIVER_INPUT_FRAME_ID:{
          subaru_hscan_driver_input_t temp;
          subaru_hscan_driver_input_unpack(&temp,veh_can_message.buf,veh_can_message.len);
        
          // Driver input
          rtd.steering_angle = subaru_hscan_driver_input_steering_angle_decode(temp.steering_angle);
          rtd.brake_pos = subaru_hscan_driver_input_brake_pos_decode(temp.brake_pos);

        }break;
        case SUBARU_HSCAN_SPEED_FRAME_ID:{
          subaru_hscan_speed_t temp;
          subaru_hscan_speed_unpack(&temp,veh_can_message.buf,veh_can_message.len);
          
          // Speed
          rtd.speed_kph = subaru_hscan_speed_veh_speed_decode(temp.veh_speed);
          rtd.brake_sw = subaru_hscan_speed_brake_sw_decode(temp.brake_sw);
          // subaru_hscan_speed_esp_sw_decode(temp.esp_sw); //I think this is the traction control button
          
        }break;
        case SUBARU_HSCAN_WHEEL_SPEED_FRAME_ID:{
          subaru_hscan_wheel_speed_t temp;
          subaru_hscan_wheel_speed_unpack(&temp,veh_can_message.buf,veh_can_message.len);
          
          // Wheel speeds
          rtd.spd_wheel_fl = subaru_hscan_wheel_speed_wss_fl_decode(temp.wss_fl);
          rtd.spd_wheel_fr = subaru_hscan_wheel_speed_wss_fr_decode(temp.wss_fr);
          rtd.spd_wheel_rl = subaru_hscan_wheel_speed_wss_rl_decode(temp.wss_rl);
          rtd.spd_wheel_rr = subaru_hscan_wheel_speed_wss_rr_decode(temp.wss_rr);

        }break;
        case SUBARU_HSCAN_BODY_STAT_1_FRAME_ID:{
          subaru_hscan_body_stat_1_t temp;
          subaru_hscan_body_stat_1_unpack(&temp,veh_can_message.buf,veh_can_message.len);
          
          // Body stat 1
          rtd.reverse_sw = subaru_hscan_body_stat_1_reverse_sw_decode(temp.reverse_sw);
          rtd.temp_ext = subaru_hscan_body_stat_1_temp_out_decode(temp.temp_out);
          rtd.wiper_sw = subaru_hscan_body_stat_1_wiper_sw_decode(temp.wiper_sw);
          rtd.bright_sw = subaru_hscan_body_stat_1_bright_sw_decode(temp.bright_sw);
          rtd.headlight_sw = subaru_hscan_body_stat_1_headlight_sw_decode(temp.headlight_sw);
          rtd.drl_sw = subaru_hscan_body_stat_1_drl_sw_decode(temp.drl_sw);
          rtd.handbrake_sw = subaru_hscan_body_stat_1_handbrake_sw_decode(temp.handbrake_sw);
          rtd.fuel_res = subaru_hscan_body_stat_1_fuel_res_decode(temp.fuel_res);

        }break;
        case SUBARU_HSCAN_BODY_STAT_2_FRAME_ID:{
          subaru_hscan_body_stat_2_t temp;
          subaru_hscan_body_stat_2_unpack(&temp,veh_can_message.buf,veh_can_message.len);
          
          // Body stat 2
          rtd.clutch_sw = subaru_hscan_body_stat_2_clutch_sw_decode(temp.clutch_sw);
          rtd.temp_eng = subaru_hscan_body_stat_2_temp_coolant_decode(temp.temp_coolant);
          rtd.fuel_consumption_inst = subaru_hscan_body_stat_2_fuel_consumption_decode(temp.fuel_consumption);
          
        }break;
        default:
          // Message not found
          break;
      }

      // update derived values
      
      // km/h / MI_TO_KM = mi/hr
      // mm3/sec * HOUR_TO_SEC / GAL_TO_MM3  = gal/hr
      // mi/hr / gal/hr = mi/gal
      if(rtd.fuel_consumption_inst == 0){
        rtd.fuel_mpg_inst = 100; 
      }else{
      rtd.fuel_mpg_inst = (rtd.speed_kph/MI_TO_KM)/
                            ((rtd.fuel_consumption_inst*HOUR_TO_SEC)/GAL_TO_MM3);
      }

      rtd.fuel_percent = ((rtd.fuel_res - FUEL_RES_EMPTY) / ((float)(FUEL_RES_FULL - FUEL_RES_EMPTY))) * 100;
    }

    #ifdef DELAYS
    //threads.delay(5);
    #endif
  }
}

void serviceRADCANTask(){
  while(1){
    // handle RAD CAN message processing here 
    while(rad_can.read(rad_can_message)){

      if(flag_debug_can){
        Serial.printf(F("Frame received! ID: %03x D:"),rad_can_message.id);
        for(int i=0;i<rad_can_message.len;i++){
          Serial.printf(F(" %02x"),rad_can_message.buf[i]);
        }
        Serial.println("");
      }

      switch(rad_can_message.id){
        case MRR_PCAN_MRR_DETECTION_001_FRAME_ID ... MRR_PCAN_MRR_DETECTION_064_FRAME_ID:{
          //decode all the frames as a detection 001 type
          mrr_pcan_mrr_detection_001_t temp;
          mrr_pcan_mrr_detection_001_unpack(&temp,rad_can_message.buf,rad_can_message.len);
          
          uint8_t index = rad_can_message.id - MRR_PCAN_MRR_DETECTION_001_FRAME_ID; // should give value from 0-63

          // uint8_t is_valid, is_nd, is_super_res, is_clutter;
          // float azimuth, range, rate; // deg, m, m/s
          // uint8_t amplitude, scan_index; // dbsm

          rad.det[index].is_valid = mrr_pcan_mrr_detection_001_can_det_valid_level_01_decode(temp.can_det_valid_level_01);
          rad.det[index].is_nd = mrr_pcan_mrr_detection_001_can_det_nd_target_01_decode(temp.can_det_nd_target_01);
          rad.det[index].is_super_res = mrr_pcan_mrr_detection_001_can_det_super_res_target_01_decode(temp.can_det_super_res_target_01);
          rad.det[index].is_clutter = mrr_pcan_mrr_detection_001_can_det_host_veh_clutter_01_decode(temp.can_det_host_veh_clutter_01);

          rad.det[index].azimuth = degrees(mrr_pcan_mrr_detection_001_can_det_azimuth_01_decode(temp.can_det_azimuth_01)); // convert to deg
          rad.det[index].range = mrr_pcan_mrr_detection_001_can_det_range_01_decode(temp.can_det_range_01);
          rad.det[index].rate = mrr_pcan_mrr_detection_001_can_det_range_rate_01_decode(temp.can_det_range_rate_01);

          rad.det[index].amplitude = mrr_pcan_mrr_detection_001_can_det_amplitude_01_decode(temp.can_det_amplitude_01);
          rad.det[index].scan_index = mrr_pcan_mrr_detection_001_can_scan_index_2_lsb_01_decode(temp.can_scan_index_2_lsb_01);
        
        }break;
        default:
          // Message not found
          break;
      }

    }

    #ifdef DELAYS
    //threads.delay(5);
    #endif
  }
}


void serviceKlineTask(){
  while(1){
    // handle KLINE message querying and processing here

    if(!ecu_init_done){
      if(flag_debug_kline) Serial.println(F("Sending ECU init"));
      writeSSM(SSM_init_msg,sizeof(SSM_init_msg)/sizeof(uint8_t),&KLINE_Serial);

      if(readSSM(SSM_scratch, sizeof(SSM_scratch)/sizeof(uint8_t),false,&KLINE_Serial)){
        if(flag_debug_kline) Serial.println(F("ECU init success!"));
        ecu_init_done = 1;
      }
    }else{ // ECU is init'd, we can poll
      if(flag_debug_kline) Serial.println(F("polling ecu over SSM"));
      uint8_t packetLen;
      genSSMPkt(SSM_poll_scratch, packetLen, 0, SSM_pid_list, sizeof(SSM_pid_list)/sizeof(uint16_t));
      writeSSM(SSM_poll_scratch, packetLen, &KLINE_Serial);
      if(readSSM(SSM_scratch, sizeof(SSM_scratch)/sizeof(uint8_t), false, &KLINE_Serial)){
        // parse data

        for(int i=0; i<(sizeof(SSM_pid_list)/sizeof(uint16_t)); i++){
          // iterate through Pid list
          if(SSM_pid_list[i] == 0x24){
            // map
            rtd.manifold_pressure = ((float)SSM_poll_scratch[i]-128)*(37.0/255.0);
          }else if(SSM_pid_list[i] == 0x11){
            // timing
            rtd.timing_advance = ((float)SSM_poll_scratch[i]-128)/2.0;
          }else if(SSM_pid_list[i] == 0x2A){
            // fuel temp
            rtd.temp_fuel = (float)SSM_poll_scratch[i]-40;
          }else if(SSM_pid_list[i] == 0x2E){
            // fuel V
            rtd.fuel_v = (float)SSM_poll_scratch[i]*0.02;
          }
        }
        
      }else{
        if(flag_debug_kline) Serial.println(F("SSM ecu poll fail"));
      }
    }
    #ifdef DELAYS
    //threads.delay(25);
    #endif
  }
}

void calcLongTerms(){ // every 1000ms

  // only update fuel level if speed has not changed by more than 5 kph 
  // TODO use longitudinal acceleration to change when not accelerating
  if(abs(rtd.speed_kph - prev_speed_kph) < 5){
    fuel_percent -= fuel_percent/(float)FUEL_AVG_CYCLES;
    fuel_percent += rtd.fuel_percent/(float)FUEL_AVG_CYCLES;
    if(millis()<EARLY_START_MS){
      // we just started, let's give the fuel level a quick refresh
      fuel_percent = rtd.fuel_percent;
    }
  }

  // always update when moving as long as we're not maxed out or under heavy accel
  if(rtd.speed_kph > 20 && rtd.fuel_mpg_inst < 100 && rtd.accel_pos < 50){
    fuel_mpg_trip -= fuel_mpg_trip / (float)MPG_AVG_CYCLES;
    fuel_mpg_trip += rtd.fuel_mpg_inst / (float)MPG_AVG_CYCLES;
  }

  // update based on our new fuel level % and long term mpg
  // do not average this, fuel % and mpg will smooth for us
  miles_to_e = (FUEL_CAP_GAL*fuel_percent/100.0)*fuel_mpg_trip;

  // update our new old speed
  prev_speed_kph = rtd.speed_kph;
}

void processGPSUpdateRTCTask(){
  while(1){
    while(GPS_Serial.available()){
      if(flag_debug_gps){
        long chars;
        short sentences, fails;
        gps.stats(&chars,&sentences,&fails);
        Serial.printf("GPS chars:%d msgs:%d fail:%d\n",chars,sentences,fails);
      }
      if(gps.encode(GPS_Serial.read())){ // got a full GPS packet
        if(flag_debug_gps) Serial.println("Got GPS packet!");
        unsigned long age;
        int Year;
        byte Month, Day, Hour, Minute, Second;
        gps.crack_datetime(&Year, &Month, &Day, &Hour, &Minute, &Second, NULL, &age);
        if (age < 500) {
          if(flag_debug_gps) Serial.printf("Age is %d. Updating time to %02d:%02d:%02d\n",Hour,Minute,Second);
          // set the Time to the latest GPS reading
          noInterrupts();
          setTime(Hour, Minute, Second, Day, Month, Year);
          // keep time in UTC locally
          //adjustTime(TZ_OFFSET * SECS_PER_HOUR);
          interrupts();
        }
      }
    }
    #ifdef DELAYS
    //threads.delay(25);
    #endif
  }
}

void updateDisplayTask(){
  auto smallFont = u8g2_font_5x7_mf;
  auto medFont = u8g2_font_profont22_mn;
  while(1){
    // clear the display - TODO remove this later for speed
    oled.clearBuffer();
    oled.setFontPosTop();
  
    // Top left display current time
    oled.setFont(medFont);
    oled.setCursor(0,0);
    oled.printf(F("%2d"), hour()+TZ_OFFSET < 0 ? 24+hour()+TZ_OFFSET : hour()+TZ_OFFSET);
    oled.setFont(smallFont);
    oled.printf(second()%2 ? F(":") : F(" ")); // sneak in small colon
    oled.setFont(medFont);
    oled.printf(F("%02d"),minute());
    oled.setFont(smallFont);
    oled.printf(F(":%02d"),second()); // flash colon every second

    // display FPS after time
    oled.printf(F(" %2.0f"),(double)1000/(millis()-loopTimer));
    oled.setCursor(leftLineX-oled.getStrWidth("FPS"),8);
    oled.print(F("FPS"));
  
    // Ext temp top right big
    oled.setFont(medFont);
    oled.setCursor(oled.getDisplayWidth()-((2*12)+(6*6)),0);
    oled.printf(F("%3.0f"),C_TO_F(rtd.temp_ext));
    oled.setFont(smallFont);
    oled.printf(F(".%01d F"), getDecimalTenth(C_TO_F(rtd.temp_ext)));
    oled.setCursor(oled.getDisplayWidth()-(3*6),8);
    oled.printf(F("Ext"));

    // wheel speeds
    oled.setFont(smallFont);
    oled.setCursor(rightLineX,0); // top left
    oled.setDrawColor(abs(rtd.speed_kph - rtd.spd_wheel_fl) > 1 ? 0 : 1);
    oled.printf(F("%2.0f "),rtd.spd_wheel_fl/MI_TO_KM);
    //oled.setCursor(rightLineX+8,0); // top right
    oled.setDrawColor(abs(rtd.speed_kph - rtd.spd_wheel_fr) > 1 ? 0 : 1);
    oled.printf(F("%-2.0f"), rtd.spd_wheel_fr/MI_TO_KM);
    oled.setCursor(rightLineX,8); // bottom left
    oled.setDrawColor(abs(rtd.speed_kph - rtd.spd_wheel_rl) > 1 ? 0 : 1);
    oled.printf(F("%2.0f "),rtd.spd_wheel_rl/MI_TO_KM);
    //oled.setCursor(rightLineX+8,8); // bottom right
    oled.setDrawColor(abs(rtd.speed_kph - rtd.spd_wheel_rr) > 1 ? 0 : 1);
    oled.printf(F("%-2.0f"),rtd.spd_wheel_rr/MI_TO_KM);
    oled.setDrawColor(1);
  
    // bottom right small
    oled.setFont(smallFont);
    oled.setCursor(rightLineX+3,rightDiv3Y+2);
    oled.printf(F("%4.1f %1d    %4d"),(rtd.accel_pos-rtd.brake_pos),rtd.gear_pos, rtd.eng_speed);
    oled.setCursor(rightLineX+3,rightDiv3Y+10);
    if(rtd.brake_sw)
      oled.printf(F(" BRK "));
    else if(rtd.handbrake_sw){
      oled.setDrawColor(0);
      oled.printf(F(" PRK "));
      oled.setDrawColor(1);
    }
    else
      oled.printf(F(" ACC "));
    if(rtd.reverse_sw)
      oled.printf(F("REV "));
    else if(rtd.clutch_sw)
      oled.printf(F("NEUT"));
    else
      oled.printf(F("GEAR"));
    oled.printf(F(" RPM"));
  
    // Economy info below ext temp
    oled.setFont(smallFont);
    oled.setCursor(rightLineX+3,rightDiv1Y+2);
    oled.printf(F("%-3.1f  %3.1f"),fuel_mpg_trip,rtd.fuel_mpg_inst);
    oled.setCursor(rightLineX+3+(9*6),rightDiv1Y+5);
    oled.printf(F("MPG"));
    oled.setCursor(rightLineX+3,rightDiv1Y+10);
    oled.printf(F("Trip  Inst"));
  
    // instant fuel use below economy
    oled.setFont(smallFont);
    oled.setCursor(rightLineX+3,rightDiv2Y+2);
    oled.printf(F("%4.3f gal/hr"),(rtd.fuel_consumption_inst*HOUR_TO_SEC)/GAL_TO_MM3);
  
    // miles to E
    oled.setFont(medFont);
    oled.setCursor(0,leftDiv1Y+2);
    oled.printf(F("%3.0f"),miles_to_e);
    oled.setFont(smallFont);
    oled.printf(F(".%01d"), getDecimalTenth(miles_to_e));
    oled.setCursor(leftLineX-3-(5*6),leftDiv1Y+2);
    oled.printf(F("miles"));
    oled.setCursor(leftLineX-3-(4*6),leftDiv1Y+2+8);
    oled.printf(F("to E"));
  
    // left left bottom big show eng temp
    oled.setFont(medFont);
    oled.setCursor(0,leftDiv2Y+3);
    oled.printf(F("%3.0f"),C_TO_F(rtd.temp_eng));
    oled.setFont(smallFont);
    oled.printf(F(".%01d"), getDecimalTenth(C_TO_F(rtd.temp_eng)));  
    oled.setCursor(0,leftDiv2Y+3+16+2);
    oled.printf(F("Eng F"));
  
    // left right bottom big show fuel %
    oled.setFont(medFont);
    oled.setCursor(leftDiv3X+2,leftDiv2Y+3);
    oled.printf(F("%2.0f"),fuel_percent);
    oled.setFont(smallFont);
    //oled.setCursor(leftDiv3X+2+11*3,leftDiv2Y+2);
    oled.printf(F(".%01d"), getDecimalTenth(fuel_percent));
    oled.setCursor(leftDiv3X+2,leftDiv2Y+3+16+2);
    oled.printf(F("fuel %%"));
  
    // gps info
    //gps.f_get_position(&lat, &lon, &age);
    //oled.setFont(smallFont);
    //oled.setCursor(0,0);
    //oled.printf(F("%3.1f MPH"), gps.f_speed_mph());
    //oled.setCursor(0,8);
    // show age
    //oled.printf(F("%4d ms"),age);
    // show course
    //oled.setCursor(11*6,0);
    //oled.printf(F("%-3s"),gps.cardinal(gps.f_course()));
    //oled.setCursor(10*6,7);
    //oled.printf(F("%3d\xA7"),gps.course());
    // put number of sats to the left of the ext temp
    //oled.setCursor(oled.getDisplayWidth()-((2*12)+(8*6)),0);
    //oled.printf(F("%3d"), gps.satellites());
    //oled.setCursor(oled.getDisplayWidth()-((2*12)+(9*6)),7);
    //oled.printf(F("sats"));

    // Cruise text
    oled.setFont(smallFont);
    oled.setCursor(leftLineX+2,oled.getDisplayHeight()-(7*3+4));
    oled.printf(F("%3.0f"), rtd.steering_angle); // SWA above cruise
    oled.setCursor(leftLineX+2,oled.getDisplayHeight()-(7*2+2));
    oled.setDrawColor(rtd.cruise_sw ? 0 : 1);
    oled.printf(F("Cru"));
    oled.setCursor(leftLineX+2,oled.getDisplayHeight()-(7));
    oled.setDrawColor(rtd.cruise_set_sw ? 0 : 1);
    oled.printf(F("Set "));
    oled.setDrawColor(1); // go back to normal
    oled.printf(F("%2d"), rtd.speed_cruise/MI_TO_KM);

    // steering wheel angle + triangle
    uint8_t distance_scale; //based on 90mph 132fps max. 6 seconds max is 792ft
    if(rtd.speed_kph/MI_TO_KM > 80) distance_scale = 40*6;      //787 ft
    else if(rtd.speed_kph/MI_TO_KM > 70) distance_scale = 35*6; //689 ft
    else if(rtd.speed_kph/MI_TO_KM > 60) distance_scale = 30*6; //591 ft
    else if(rtd.speed_kph/MI_TO_KM > 50) distance_scale = 25*6; //492 ft
    else if(rtd.speed_kph/MI_TO_KM > 40) distance_scale = 20*6; //394 ft
    else if(rtd.speed_kph/MI_TO_KM > 30) distance_scale = 15*6; //295 ft
    else if(rtd.speed_kph/MI_TO_KM > 20) distance_scale = 10*6; //197 ft
    else if(rtd.speed_kph/MI_TO_KM > 10) distance_scale = 5*6;  //98 ft
    else if(rtd.speed_kph/MI_TO_KM >  5) distance_scale = 2*6;  //39 ft
    else if(rtd.speed_kph/MI_TO_KM >  2) distance_scale = 1*6;  //20 ft
    else distance_scale = 2;                                    //6.5 ft
    int8_t swa_x = (rightLineX-x_ctr) * sin(radians(rtd.steering_angle)); // negative is left turn
    oled.drawLine(leftLineX,leftDiv1Y,x_ctr,oled.getDisplayHeight()+1); // left angle leg
    oled.drawLine(rightLineX,leftDiv1Y,x_ctr,oled.getDisplayHeight()+1); // right angle leg
    //oled.drawEllipse(x_ctr,leftDiv1Y,x_ctr-leftLineX,leftDiv1Y,U8G2_DRAW_UPPER_RIGHT|U8G2_DRAW_UPPER_LEFT); //semicircle
    oled.drawLine(x_ctr,oled.getDisplayHeight()+1,x_ctr+swa_x,0); // Y always at display top
    oled.setCursor(rightLineX-(5*5+2),oled.getDisplayHeight()-7);
    oled.printf(F("%3u m"),distance_scale); // put the scale down there

    // radar points
    // uint8_t is_valid, is_nd, is_super_res, is_clutter;
    // float azimuth, range, rate; // deg, m, m/s
    // uint8_t amplitude, scan_index; // dbsm
    for(uint8_t i=0;i<NUM_DETECTIONS;i++){
      // each detection we check valid, if valid and in range we plot. 
      if(rad.det[i].is_valid && rad.det[i].range < distance_scale){
        int8_t det_x = (rightLineX-x_ctr) * sin(radians(rad.det[i].azimuth));
        uint8_t det_y = rad.det[i].range * oled.getDisplayHeight() / distance_scale;
        oled.drawPixel(x_ctr+det_x,oled.getDisplayHeight()+1-det_y);
      }
    }

    // verts
    oled.drawLine(leftLineX,leftDiv1Y,leftLineX,oled.getDisplayHeight());
    oled.drawLine(rightLineX,leftDiv1Y,rightLineX,oled.getDisplayHeight());
    oled.drawLine(leftDiv3X,leftDiv2Y,leftDiv3X,oled.getDisplayHeight());
    // horizos
    oled.drawLine(0,leftDiv1Y,leftLineX,leftDiv1Y);
    oled.drawLine(0,leftDiv2Y,leftLineX,leftDiv2Y);
    oled.drawLine(rightLineX,rightDiv1Y,oled.getDisplayWidth(),rightDiv1Y);
    oled.drawLine(rightLineX,rightDiv2Y,oled.getDisplayWidth(),rightDiv2Y);
    oled.drawLine(rightLineX,rightDiv3Y,oled.getDisplayWidth(),rightDiv3Y);
    
    oled.sendBuffer();
    loopTimer = millis();

    #ifdef DELAYS
    threads.delay(25);
    #endif
  }
}

uint8_t checkSumSSM(uint8_t sum){
  byte counter = 0;
  byte power = 1;
  for(uint8_t n = 0; n < 8; n++){
    counter += bitRead(sum,n)*power;
    power = power*2;
  }
  return counter;
}

void writeSSM(uint8_t data[], uint8_t length, HardwareSerial* serial){
  //Serial.println(F("Sending SSM packet... "));
  for(uint8_t x = 0; x < length; x++){
    serial->write(data[x]);
  }
  //Serial.println(F("done sending."));
}

uint8_t readSSM(uint8_t* dataArray, uint8_t dataArrayLength, uint8_t nonZeroes, HardwareSerial* serial){
  uint8_t data = 0;
  uint8_t isPacket = false;
  uint8_t sumBytes = 0;
  uint8_t checkSumByte = 0;
  uint8_t dataSize = 0;
  uint8_t bytePlace = 0;
  uint8_t zeroesLoopSpot = 0;
  uint8_t loopLength = 4;
  
  for(uint8_t j = 0; j < loopLength; j++){    
    data = serial->read();
    if(flag_debug_kline) Serial.print(F("data: ")); //diagnostic: shows any data stream
    if(flag_debug_kline) Serial.println(data);  //somehow, the delay? from these diagnostic lines allows the program to work..
  
    if(data == 0x80 && dataSize == 0){  //0x80 or 128 marks the beginning of a packet
     isPacket = true;
     if(flag_debug_kline) Serial.println(F("Begin Packet"));
     j = 0;
    }
    
    //terminate function and return false if no response is detected
    if(j == (loopLength - 1) && !isPacket)
    {
      if(flag_debug_kline) Serial.println(F("no response detected"));
      return false;
    }
  
   if(isPacket && data != -1){
     if(flag_debug_kline) Serial.println(data); // for debugging: shows in-packet data
   
     if(bytePlace == 3){ // how much data is coming
       dataSize = data;
       //Serial.print(F("dataSize: "));
       //Serial.println(dataSize);
       loopLength = data + 6;
     }  
     
     if(bytePlace > 4 && bytePlace-5 < dataArrayLength && nonZeroes == false)
     {
       dataArray[bytePlace-5] = data;
     }
     else if(bytePlace > 4 && zeroesLoopSpot < dataArrayLength/2 && nonZeroes == true && data != 0 && bytePlace < dataSize + 4)
     {
       dataArray[zeroesLoopSpot] = data;
       dataArray[zeroesLoopSpot + (dataArrayLength / 2)] = bytePlace;
       zeroesLoopSpot++;
     }
         
     bytePlace += 1; //increment bytePlace
   
     //once the data is all recieved, checksum and re-set counters
     if(bytePlace == dataSize+5){
       checkSumByte = checkSumSSM(sumBytes);  //the 8 least significant bits of sumBytes
     
       if(data != checkSumByte){
         if(flag_debug_kline) Serial.println(F("checksum error"));
         return false;
       }
     
       isPacket = false;
       sumBytes = 0;
       bytePlace = 0;
       checkSumByte = 0;
       dataSize = 0;
       if(flag_debug_kline) Serial.println(F("End Packet"));
       return true;
     }
     else{
       sumBytes += data; // this is to compare with the checksum byte
       //Serial.print(F("sum: "));
       //Serial.println(sumBytes);
     }
   }
  }
}


void genSSMPkt(uint8_t* result, uint8_t &resultLength, uint8_t po, const uint16_t* pids, uint8_t numPids){
  // PO should be 0 unless we want a datastream

  resultLength = 0;
  result[0] = 0x80;           // header SOF
  result[1] = 0x10;           // dest, ECU
  result[2] = 0xF0;           // source, diag tool
  result[3] = (7+3*numPids);  // contains length 7+3*num_pids
  result[4] = 0xA8;           // single addr read
  result[5] = po;             // po, 0 for single, 1 for stream

  resultLength += 6;

  for( int i=0; i<numPids; i++){
    if(resultLength+3 >= sizeof(SSM_poll_scratch)/sizeof(uint8_t)){
      // we would overflow our buffer, so skip the rest
      if(flag_debug_kline) Serial.println(F("skipping last pids, packet would be too large"));
      break;
    }
    
    // take the least significant 3 bytes from each pid and add them to the result
    result[6+(3*i)] = pids[i] & 0x000000FF;
    result[7+(3*i)] = pids[i] & 0x0000FF00;
    result[8+(3*i)] = pids[i] & 0x00FF0000;
    resultLength += 3;
  }

  // calculate and append the checksum
  uint8_t sumBytes = 0;
  for(int i=0; i<resultLength; i++)
    sumBytes += result[i];
    
  result[resultLength] = checkSumSSM(sumBytes);
}

inline uint8_t getDecimalTenth(float val){
  return 10*(val-floorf(val));
}

inline void petWdt(){
  uint8_t happy_flag = true;
  for(int i=0; i< (sizeof(thread_pids)/sizeof(uint8_t)); i++){
      if(threads.getState(thread_pids[i]) != Threads::RUNNING)
        happy_flag = false;
  }
  if(happy_flag){
    //digitalWrite(LED5,LOW);
    noInterrupts();
    //wdt.loop(); //pet the dog
    interrupts();
  }
}
