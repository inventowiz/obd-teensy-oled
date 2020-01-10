EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L dk_Interface-Drivers-Receivers-Transceivers:MCP2551-I_SN U2
U 1 1 5DDC7610
P 10150 6000
F 0 "U2" H 10400 5700 60  0000 C CNN
F 1 "MCP2551-I_SN" H 10650 5600 60  0000 C CNN
F 2 "digikey-footprints:SOIC-8_W3.9mm" H 10350 6200 60  0001 L CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en011797" H 10350 6300 60  0001 L CNN
F 4 "MCP2551-I/SN-ND" H 10350 6400 60  0001 L CNN "Digi-Key_PN"
F 5 "MCP2551-I/SN" H 10350 6500 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 10350 6600 60  0001 L CNN "Category"
F 7 "Interface - Drivers, Receivers, Transceivers" H 10350 6700 60  0001 L CNN "Family"
F 8 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en011797" H 10350 6800 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/microchip-technology/MCP2551-I-SN/MCP2551-I-SN-ND/509452" H 10350 6900 60  0001 L CNN "DK_Detail_Page"
F 10 "IC TRANSCEIVER CAN HI-SPD 8-SOIC" H 10350 7000 60  0001 L CNN "Description"
F 11 "Microchip Technology" H 10350 7100 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10350 7200 60  0001 L CNN "Status"
	1    10150 6000
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:OBDII J1
U 1 1 5DDC9443
P 5550 1450
F 0 "J1" H 5550 2160 45  0000 C CNN
F 1 "OBDII" H 5550 2076 45  0000 C CNN
F 2 "Connectors:OBDII" H 5550 2000 20  0001 C CNN
F 3 "" H 5550 1450 50  0001 C CNN
F 4 "DEV-09911" H 5550 1981 60  0000 C CNN "Field4"
	1    5550 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 5800 9750 5800
Text GLabel 4650 1600 0    50   BiDi ~ 0
CAN_P
Text GLabel 6450 1600 2    50   BiDi ~ 0
CAN_N
Text GLabel 9750 5900 0    50   BiDi ~ 0
CAN_N
Text GLabel 9750 6000 0    50   BiDi ~ 0
CAN_P
$Comp
L SparkFun-PowerSymbols:GND #GND0101
U 1 1 5DDECCD7
P 5000 5500
F 0 "#GND0101" H 5050 5450 45  0001 L BNN
F 1 "GND" H 5000 5330 45  0000 C CNN
F 2 "" H 5000 5400 60  0001 C CNN
F 3 "" H 5000 5400 60  0001 C CNN
	1    5000 5500
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0102
U 1 1 5DDED7DE
P 10150 6300
F 0 "#GND0102" H 10200 6250 45  0001 L BNN
F 1 "GND" H 10150 6130 45  0000 C CNN
F 2 "" H 10150 6200 60  0001 C CNN
F 3 "" H 10150 6200 60  0001 C CNN
	1    10150 6300
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0103
U 1 1 5DDF0EE4
P 7150 2400
F 0 "#GND0103" H 7200 2350 45  0001 L BNN
F 1 "GND" H 7150 2230 45  0000 C CNN
F 2 "" H 7150 2300 60  0001 C CNN
F 3 "" H 7150 2300 60  0001 C CNN
	1    7150 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2700 7400 2400
Wire Wire Line
	7400 2400 7150 2400
$Comp
L SparkFun-PowerSymbols:GND #GND0104
U 1 1 5DDF6596
P 3850 1750
F 0 "#GND0104" H 3900 1700 45  0001 L BNN
F 1 "GND" H 3850 1580 45  0000 C CNN
F 2 "" H 3850 1650 60  0001 C CNN
F 3 "" H 3850 1650 60  0001 C CNN
	1    3850 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 1500 3850 1500
Wire Wire Line
	3850 1500 3850 1750
Text GLabel 4650 1700 0    50   BiDi ~ 0
KLINE
$Comp
L SparkFun-PowerSymbols:GND #GND0105
U 1 1 5DDF957E
P 6450 5350
F 0 "#GND0105" H 6500 5300 45  0001 L BNN
F 1 "GND" H 6450 5180 45  0000 C CNN
F 2 "" H 6450 5250 60  0001 C CNN
F 3 "" H 6450 5250 60  0001 C CNN
	1    6450 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 5100 6450 5100
Wire Wire Line
	6450 5100 6450 5350
Wire Wire Line
	6200 5700 6200 5200
$Comp
L SparkFun-PowerSymbols:V_BATT #SUPPLY0102
U 1 1 5DE01483
P 7250 1000
F 0 "#SUPPLY0102" H 7300 1000 45  0001 L BNN
F 1 "V_BATT" H 7250 1276 45  0000 C CNN
F 2 "XXX-00000" H 7250 1181 60  0000 C CNN
F 3 "" H 7250 1000 60  0001 C CNN
	1    7250 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1800 7250 1800
Wire Wire Line
	7250 1800 7250 1700
Wire Wire Line
	5000 5000 4700 5000
Wire Wire Line
	4700 5000 4700 4600
$Comp
L dk_Diodes-Rectifiers-Single:1N4007-T_NRND D2
U 1 1 5DE09084
P 7250 1500
F 0 "D2" V 7303 1422 60  0000 R CNN
F 1 "1N4007-T_NRND" V 7197 1422 60  0000 R CNN
F 2 "digikey-footprints:DO-41" H 7450 1700 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds28002.pdf" H 7450 1800 60  0001 L CNN
F 4 "1N4007DICT-ND" H 7450 1900 60  0001 L CNN "Digi-Key_PN"
F 5 "1N4007-T" H 7450 2000 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 7450 2100 60  0001 L CNN "Category"
F 7 "Diodes - Rectifiers - Single" H 7450 2200 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds28002.pdf" H 7450 2300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/1N4007-T/1N4007DICT-ND/76454" H 7450 2400 60  0001 L CNN "DK_Detail_Page"
F 10 "DIODE GEN PURP 1KV 1A DO41" H 7450 2500 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 7450 2600 60  0001 L CNN "Manufacturer"
F 12 "Not For New Designs" H 7450 2700 60  0001 L CNN "Status"
	1    7250 1500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7250 1300 7250 1000
Connection ~ 4700 4600
Text GLabel 6200 5000 2    50   Input ~ 0
KLINE_EN
Text GLabel 7400 3100 0    50   Output ~ 0
KLINE_EN
$Comp
L SparkFun-PowerSymbols:GND #GND0106
U 1 1 5DE2D9F6
P 6600 4300
F 0 "#GND0106" H 6650 4250 45  0001 L BNN
F 1 "GND" H 6600 4130 45  0000 C CNN
F 2 "" H 6600 4200 60  0001 C CNN
F 3 "" H 6600 4200 60  0001 C CNN
	1    6600 4300
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0103
U 1 1 5DE2DFA9
P 10850 5100
F 0 "#SUPPLY0103" H 10900 5100 45  0001 L BNN
F 1 "3.3V" H 10850 5376 45  0000 C CNN
F 2 "XXX-00000" H 10850 5281 60  0000 C CNN
F 3 "" H 10850 5100 60  0001 C CNN
	1    10850 5100
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:5V #SUPPLY0104
U 1 1 5DE2E90D
P 10850 4600
F 0 "#SUPPLY0104" H 10900 4600 45  0001 L BNN
F 1 "5V" H 10850 4876 45  0000 C CNN
F 2 "XXX-00000" H 10850 4781 60  0000 C CNN
F 3 "" H 10850 4600 60  0001 C CNN
	1    10850 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 5200 10850 5200
Wire Wire Line
	10850 5200 10850 5100
Wire Wire Line
	9600 5000 10200 5000
Wire Wire Line
	10500 5000 10500 4600
Wire Wire Line
	10500 4600 10850 4600
Text Notes 9750 4650 0    50   ~ 0
Note: Cut trace on \nTeensy to seperate \nVIN from VUSB!
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0105
U 1 1 5DE3EA2A
P 6600 4150
F 0 "#SUPPLY0105" H 6650 4150 45  0001 L BNN
F 1 "3.3V" H 6600 4426 45  0000 C CNN
F 2 "XXX-00000" H 6600 4331 60  0000 C CNN
F 3 "" H 6600 4150 60  0001 C CNN
	1    6600 4150
	1    0    0    -1  
$EndComp
NoConn ~ 9600 3600
NoConn ~ 9600 3500
NoConn ~ 9600 3400
NoConn ~ 9600 3300
NoConn ~ 9600 3200
NoConn ~ 9600 3100
NoConn ~ 9600 3000
NoConn ~ 9600 2900
NoConn ~ 9600 2800
NoConn ~ 9600 2700
NoConn ~ 9600 3700
NoConn ~ 9600 3800
NoConn ~ 9600 3900
NoConn ~ 9600 4000
NoConn ~ 9600 4100
NoConn ~ 9600 4200
NoConn ~ 9600 4300
Text Notes 9750 3100 3    50   ~ 0
Do not use bottom pads
Text GLabel 7400 3800 0    50   Output ~ 0
SPI_CS
Text GLabel 7400 3900 0    50   Output ~ 0
SPI_DOUT
Text GLabel 7400 4000 0    50   Input ~ 0
SPI_DIN
Text GLabel 7400 4600 0    50   Output ~ 0
SPI_SCK
Text GLabel 9250 1200 2    50   Input ~ 0
SPI_DOUT
Text GLabel 9250 1100 2    50   Output ~ 0
SPI_DIN
Text GLabel 9250 1300 2    50   Input ~ 0
SPI_CS
Text GLabel 9250 1000 2    50   Input ~ 0
SPI_SCK
$Comp
L SparkFun-PowerSymbols:GND #GND0107
U 1 1 5DE6D968
P 10350 850
F 0 "#GND0107" H 10400 800 45  0001 L BNN
F 1 "GND" H 10350 680 45  0000 C CNN
F 2 "" H 10350 750 60  0001 C CNN
F 3 "" H 10350 750 60  0001 C CNN
	1    10350 850 
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:5V #SUPPLY0106
U 1 1 5DE6E6C2
P 10350 1600
F 0 "#SUPPLY0106" H 10400 1600 45  0001 L BNN
F 1 "5V" H 10350 1876 45  0000 C CNN
F 2 "XXX-00000" H 10350 1781 60  0000 C CNN
F 3 "" H 10350 1600 60  0001 C CNN
	1    10350 1600
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0107
U 1 1 5DE6EE36
P 10350 2050
F 0 "#SUPPLY0107" H 10400 2050 45  0001 L BNN
F 1 "3.3V" H 10350 2326 45  0000 C CNN
F 2 "XXX-00000" H 10350 2231 60  0000 C CNN
F 3 "" H 10350 2050 60  0001 C CNN
	1    10350 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 6200 2450 6500
Wire Wire Line
	2700 6500 2450 6500
Text GLabel 2700 6600 0    50   Input ~ 0
PWR_EN
$Comp
L SparkFun-PowerSymbols:GND #GND01
U 1 1 5DEB1BF8
P 2450 6850
F 0 "#GND01" H 2500 6800 45  0001 L BNN
F 1 "GND" H 2450 6680 45  0000 C CNN
F 2 "" H 2450 6750 60  0001 C CNN
F 3 "" H 2450 6750 60  0001 C CNN
	1    2450 6850
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:V_BATT #SUPPLY01
U 1 1 5DEAEE90
P 2450 6200
F 0 "#SUPPLY01" H 2500 6200 45  0001 L BNN
F 1 "V_BATT" H 2450 6476 45  0000 C CNN
F 2 "XXX-00000" H 2450 6381 60  0000 C CNN
F 3 "" H 2450 6200 60  0001 C CNN
	1    2450 6200
	1    0    0    -1  
$EndComp
Text GLabel 6450 1700 2    50   BiDi ~ 0
LLINE
Wire Wire Line
	5000 5200 5000 5500
$Comp
L SparkFun-PowerSymbols:5V #SUPPLY0108
U 1 1 5DE09268
P 10150 5600
F 0 "#SUPPLY0108" H 10200 5600 45  0001 L BNN
F 1 "5V" H 10150 5876 45  0000 C CNN
F 2 "XXX-00000" H 10150 5781 60  0000 C CNN
F 3 "" H 10150 5600 60  0001 C CNN
	1    10150 5600
	1    0    0    -1  
$EndComp
$Comp
L brian-custom:TPS563200DDCR U4
U 1 1 5DE1E69D
P 3000 6450
F 0 "U4" H 3025 6625 50  0000 C CNN
F 1 "TPS563200DDCR" H 3025 6534 50  0000 C CNN
F 2 "digikey-footprints:SOT-23-6" H 3000 6050 50  0001 C CNN
F 3 "" H 3000 6500 50  0001 C CNN
	1    3000 6450
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:22UF-1210-16V-20% C1
U 1 1 5DE21DA5
P 2100 6650
F 0 "C1" H 1992 6605 45  0000 R CNN
F 1 "22uF" H 1992 6689 45  0000 R CNN
F 2 "1210" H 2100 6900 20  0001 C CNN
F 3 "" H 2100 6650 50  0001 C CNN
F 4 "XXX-00000" H 1992 6784 60  0000 R CNN "Field4"
	1    2100 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 6450 2350 6450
Wire Wire Line
	2350 6450 2350 6500
Wire Wire Line
	2350 6500 2450 6500
Connection ~ 2450 6500
Wire Wire Line
	2100 6750 2100 6850
Wire Wire Line
	2100 6850 2450 6850
Wire Wire Line
	2450 6850 2700 6850
Wire Wire Line
	2700 6850 2700 6700
Connection ~ 2450 6850
$Comp
L SparkFun-Resistors:RESISTOR0603 R6
U 1 1 5DE2AA43
P 4050 6900
F 0 "R6" V 4145 6832 45  0000 R CNN
F 1 "56.2k" V 4061 6832 45  0000 R CNN
F 2 "0603" H 4050 7050 20  0001 C CNN
F 3 "" H 4050 6900 60  0001 C CNN
F 4 " " V 3966 6832 60  0000 R CNN "Field4"
	1    4050 6900
	0    1    1    0   
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-0603-25V-5% C2
U 1 1 5DE2BDF4
P 3650 6500
F 0 "C2" H 3758 6645 45  0000 L CNN
F 1 "0.1uF" H 3758 6561 45  0000 L CNN
F 2 "0603" H 3650 6750 20  0001 C CNN
F 3 "" H 3650 6500 50  0001 C CNN
F 4 "CAP-08604" H 3758 6466 60  0000 L CNN "Field4"
	1    3650 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 6700 3450 6700
Wire Wire Line
	3450 6700 3450 7100
Wire Wire Line
	3450 7100 4050 7100
Connection ~ 4050 7100
Wire Wire Line
	4050 7500 2700 7500
Wire Wire Line
	2700 7500 2700 6850
Connection ~ 2700 6850
Wire Wire Line
	3350 6600 3650 6600
Wire Wire Line
	3350 6500 3500 6500
Wire Wire Line
	3500 6500 3500 6300
Wire Wire Line
	3500 6300 3650 6300
$Comp
L SparkFun-PowerSymbols:5V #SUPPLY0109
U 1 1 5DE5F15D
P 4250 6000
F 0 "#SUPPLY0109" H 4300 6000 45  0001 L BNN
F 1 "5V" H 4250 6276 45  0000 C CNN
F 2 "XXX-00000" H 4250 6181 60  0000 C CNN
F 3 "" H 4250 6000 60  0001 C CNN
	1    4250 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 7500 4250 7500
Wire Wire Line
	4250 7500 4250 7250
Connection ~ 4050 7500
$Comp
L brian-custom:IHLP2020BZER4R7M11 L1
U 1 1 5DE7FDA3
P 3850 6100
F 0 "L1" H 3850 6325 50  0000 C CNN
F 1 "4.7uH" H 3850 6234 50  0000 C CNN
F 2 "brian-custom:IHLP2020BZER4R7M11" H 3900 5950 50  0001 C CNN
F 3 "" H 3850 6200 50  0001 C CNN
	1    3850 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 6300 3650 6100
Wire Wire Line
	3650 6100 3700 6100
Connection ~ 3650 6300
Wire Wire Line
	4000 6100 4050 6100
Wire Wire Line
	4050 6700 4050 6100
Connection ~ 4050 6100
Wire Wire Line
	4250 6000 4250 6100
Wire Wire Line
	4050 6100 4250 6100
Connection ~ 4250 6100
$Comp
L SparkFun-Resistors:RESISTOR0603 R7
U 1 1 5DE2D507
P 4050 7300
F 0 "R7" V 4145 7232 45  0000 R CNN
F 1 "10.0k" V 4061 7232 45  0000 R CNN
F 2 "0603" H 4050 7450 20  0001 C CNN
F 3 "" H 4050 7300 60  0001 C CNN
F 4 " " V 3966 7232 60  0000 R CNN "Field4"
	1    4050 7300
	0    1    1    0   
$EndComp
$Comp
L SparkFun-Capacitors:10UF-1210-50V-20% C3
U 1 1 5DEC416F
P 4250 7150
F 0 "C3" H 4358 7295 45  0000 L CNN
F 1 "47uF" H 4358 7211 45  0000 L CNN
F 2 "1210" H 4250 7400 20  0001 C CNN
F 3 "" H 4250 7150 50  0001 C CNN
F 4 "CAP-09824" H 4358 7116 60  0000 L CNN "Field4"
	1    4250 7150
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R4
U 1 1 5DEC7DB5
P 1500 7150
F 0 "R4" V 1405 7218 45  0000 L CNN
F 1 "1k-DNP" V 1489 7218 45  0000 L CNN
F 2 "0603" H 1500 7300 20  0001 C CNN
F 3 "" H 1500 7150 60  0001 C CNN
F 4 " " V 1584 7218 60  0000 L CNN "Field4"
	1    1500 7150
	0    -1   -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R5
U 1 1 5DEC7DBC
P 1700 7150
F 0 "R5" V 1605 7218 45  0000 L CNN
F 1 "1k" V 1689 7218 45  0000 L CNN
F 2 "0603" H 1700 7300 20  0001 C CNN
F 3 "" H 1700 7150 60  0001 C CNN
F 4 " " V 1784 7218 60  0000 L CNN "Field4"
	1    1700 7150
	0    1    1    0   
$EndComp
Text GLabel 1350 6750 0    50   Output ~ 0
PWR_EN
$Comp
L SparkFun-PowerSymbols:V_BATT #SUPPLY0110
U 1 1 5DED6513
P 850 7250
F 0 "#SUPPLY0110" H 900 7250 45  0001 L BNN
F 1 "V_BATT" H 850 7526 45  0000 C CNN
F 2 "XXX-00000" H 850 7431 60  0000 C CNN
F 3 "" H 850 7250 60  0001 C CNN
	1    850  7250
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0108
U 1 1 5DED89F9
P 1700 7350
F 0 "#GND0108" H 1750 7300 45  0001 L BNN
F 1 "GND" H 1700 7180 45  0000 C CNN
F 2 "" H 1700 7250 60  0001 C CNN
F 3 "" H 1700 7250 60  0001 C CNN
	1    1700 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 7350 850  7350
Wire Wire Line
	850  7350 850  7250
Wire Wire Line
	1700 6950 1700 6750
Wire Wire Line
	1700 6750 1500 6750
Wire Wire Line
	1500 6950 1500 6750
Connection ~ 1500 6750
Wire Wire Line
	1500 6750 1350 6750
Text Notes 950  7450 0    50   ~ 0
Default: Disable
Text GLabel 9250 1600 2    50   Output ~ 0
PWR_EN
$Comp
L RF_GPS:NEO-M8T U5
U 1 1 5DF03982
P 1800 3300
F 0 "U5" H 1800 2211 50  0000 C CNN
F 1 "NEO-M8T" H 1800 2120 50  0000 C CNN
F 2 "RF_GPS:ublox_NEO" H 2200 2350 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/NEO-LEA-M8T-FW3_DataSheet_%28UBX-15025193%29.pdf" H 1800 3300 50  0001 C CNN
	1    1800 3300
	1    0    0    -1  
$EndComp
$Comp
L teensy:Teensy4.0 U3
U 1 1 5DF1375B
P 8500 4050
F 0 "U3" H 8500 5665 50  0000 C CNN
F 1 "Teensy4.0" H 8500 5574 50  0000 C CNN
F 2 "teensy:Teensy40" H 8100 4250 50  0001 C CNN
F 3 "" H 8100 4250 50  0001 C CNN
	1    8500 4050
	1    0    0    -1  
$EndComp
NoConn ~ 9600 4400
NoConn ~ 9600 4500
NoConn ~ 9600 4600
$Comp
L power:GNDPWR #PWR0101
U 1 1 5DFA1519
P 3600 1600
F 0 "#PWR0101" H 3600 1400 50  0001 C CNN
F 1 "GNDPWR" H 3604 1446 50  0000 C CNN
F 2 "" H 3600 1550 50  0001 C CNN
F 3 "" H 3600 1550 50  0001 C CNN
	1    3600 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 1400 3600 1400
Wire Wire Line
	3600 1400 3600 1600
Text GLabel 1100 3900 0    50   Input ~ 0
GPS_RSTn
Text GLabel 1100 2900 0    50   Output ~ 0
GPS_TX
Text GLabel 1100 3000 0    50   Input ~ 0
GPS_RX
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0111
U 1 1 5DFA8C5B
P 1600 1200
F 0 "#SUPPLY0111" H 1650 1200 45  0001 L BNN
F 1 "3.3V" H 1600 1476 45  0000 C CNN
F 2 "XXX-00000" H 1600 1381 60  0000 C CNN
F 3 "" H 1600 1200 60  0001 C CNN
	1    1600 1200
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0109
U 1 1 5DFACE2A
P 2200 4400
F 0 "#GND0109" H 2250 4350 45  0001 L BNN
F 1 "GND" H 2200 4230 45  0000 C CNN
F 2 "" H 2200 4300 60  0001 C CNN
F 3 "" H 2200 4300 60  0001 C CNN
	1    2200 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4300 2200 4300
Wire Wire Line
	2200 4300 2200 4400
Text GLabel 2500 3600 2    50   Output ~ 0
GPS_PPS
$Comp
L SparkFun-PowerSymbols:GND #GND0110
U 1 1 5DFB4E87
P 2950 2200
F 0 "#GND0110" H 3000 2150 45  0001 L BNN
F 1 "GND" H 2950 2030 45  0000 C CNN
F 2 "" H 2950 2100 60  0001 C CNN
F 3 "" H 2950 2100 60  0001 C CNN
	1    2950 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2300 1800 2200
Text GLabel 1100 3800 0    50   Output ~ 0
GPS_PPS2
Wire Wire Line
	1700 2300 1700 2000
Wire Wire Line
	2900 2000 2900 2200
Connection ~ 2900 2200
Wire Wire Line
	2900 2200 2950 2200
Text Label 1750 2000 0    50   ~ 0
VCOIN
$Comp
L SparkFun-Resistors:RESISTOR0603 R8
U 1 1 5DFD501A
P 1700 1800
F 0 "R8" V 1605 1868 45  0000 L CNN
F 1 "0-DNP" V 1689 1868 45  0000 L CNN
F 2 "0603" H 1700 1950 20  0001 C CNN
F 3 "" H 1700 1800 60  0001 C CNN
F 4 " " V 1784 1868 60  0000 L CNN "Field4"
	1    1700 1800
	0    1    1    0   
$EndComp
Connection ~ 1700 2000
Wire Wire Line
	1800 2200 2900 2200
Wire Wire Line
	1600 1200 1600 1350
Wire Wire Line
	1700 1600 1700 1350
Wire Wire Line
	1700 1350 1600 1350
Connection ~ 1600 1350
Wire Wire Line
	1600 1350 1600 2300
Text Notes 1750 1650 0    50   ~ 0
Install to disable\nbattery backup
Wire Wire Line
	2500 3300 2900 3300
NoConn ~ 7400 2800
NoConn ~ 7400 2900
Text Notes 7300 2900 2    50   ~ 0
UART1 shared\nwith USB
NoConn ~ 7400 4400
NoConn ~ 7400 4500
$Comp
L SparkFun-PowerSymbols:GND #GND0111
U 1 1 5E036F57
P 9850 5100
F 0 "#GND0111" H 9900 5050 45  0001 L BNN
F 1 "GND" H 9850 4930 45  0000 C CNN
F 2 "" H 9850 5000 60  0001 C CNN
F 3 "" H 9850 5000 60  0001 C CNN
	1    9850 5100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 5100 9850 5100
Text GLabel 7400 4700 0    50   Output ~ 0
GPS_RX
Text GLabel 7400 4800 0    50   Input ~ 0
GPS_TX
Text Label 6800 1800 0    50   ~ 0
VBATT_RAW
$Comp
L SN65HVDA195QDRQ1:SN65HVDA195QDRQ1 U1
U 1 1 5DDCD934
P 6200 4900
F 0 "U1" H 6849 5110 60  0000 C CNN
F 1 "SN65HVDA195QDRQ1" H 6849 5023 60  0000 C CNN
F 2 "SN65HVDA195QDRQ1:SN65HVDA195QDRQ1" H 7400 5140 60  0001 C CNN
F 3 "" H 6200 4900 60  0000 C CNN
	1    6200 4900
	-1   0    0    -1  
$EndComp
Text GLabel 9750 6100 0    50   Input ~ 0
CAN_ENn
Text GLabel 7400 3000 0    50   Output ~ 0
CAN_ENn
NoConn ~ 10550 6000
NoConn ~ 5000 4900
Wire Wire Line
	9600 5400 9600 5800
Wire Wire Line
	9850 5250 9850 5300
Wire Wire Line
	9850 5300 9600 5300
Wire Wire Line
	10550 5250 9850 5250
Wire Wire Line
	10550 5900 10550 5250
Text GLabel 7400 4100 0    50   Input ~ 0
VCOIN
$Comp
L SparkFun-Resistors:RESISTOR0603 R9
U 1 1 5E0F24CD
P 9800 4900
F 0 "R9" H 9700 5100 45  0000 C CNN
F 1 "0-DNP" H 9750 5000 45  0000 C CNN
F 2 "0603" H 9800 5050 20  0001 C CNN
F 3 "" H 9800 4900 60  0001 C CNN
F 4 " " H 9800 5021 60  0000 C CNN "Field4"
	1    9800 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 4900 10200 4900
Wire Wire Line
	10200 4900 10200 5000
Connection ~ 10200 5000
Wire Wire Line
	10200 5000 10500 5000
Text Notes 9900 4850 0    50   ~ 0
Install for dev
Wire Wire Line
	10350 800  10350 850 
$Comp
L SparkFun-Resistors:RESISTOR0603 R10
U 1 1 5E167B54
P 8200 6100
F 0 "R10" H 8200 6300 45  0000 C CNN
F 1 "120-DNP" H 8200 6200 45  0000 C CNN
F 2 "0603" H 8200 6250 20  0001 C CNN
F 3 "" H 8200 6100 60  0001 C CNN
F 4 " " H 8200 6221 60  0000 C CNN "Field4"
	1    8200 6100
	1    0    0    -1  
$EndComp
Text Notes 7900 6350 0    50   ~ 0
Install for\nCAN termination
Text GLabel 8000 6100 0    50   Input ~ 0
CAN_N
Text GLabel 8400 6100 2    50   Input ~ 0
CAN_P
$Comp
L SparkFun-Coils:FERRITE_BEAD-0603 FB1
U 1 1 5E173B7E
P 3400 950
F 0 "FB1" V 3124 950 45  0000 C CNN
F 1 "FERRITE_BEAD-0603" V 3208 950 45  0000 C CNN
F 2 "0603" H 3400 1250 20  0001 C CNN
F 3 "" H 3400 950 50  0001 C CNN
F 4 "NDUC-07859" V 3303 950 60  0000 C CNN "Field4"
	1    3400 950 
	0    1    1    0   
$EndComp
$Comp
L power:GNDPWR #PWR0102
U 1 1 5E174759
P 3200 950
F 0 "#PWR0102" H 3200 750 50  0001 C CNN
F 1 "GNDPWR" H 3204 796 50  0000 C CNN
F 2 "" H 3200 900 50  0001 C CNN
F 3 "" H 3200 900 50  0001 C CNN
	1    3200 950 
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0112
U 1 1 5E17586A
P 3600 950
F 0 "#GND0112" H 3650 900 45  0001 L BNN
F 1 "GND" H 3600 780 45  0000 C CNN
F 2 "" H 3600 850 60  0001 C CNN
F 3 "" H 3600 850 60  0001 C CNN
	1    3600 950 
	1    0    0    -1  
$EndComp
Text Notes 7100 1500 2    50   ~ 0
Remove pin 13\nfrom connector
NoConn ~ 6450 1500
NoConn ~ 6450 1400
NoConn ~ 6450 1300
NoConn ~ 6450 1200
NoConn ~ 6450 1100
NoConn ~ 4650 1100
NoConn ~ 4650 1200
NoConn ~ 4650 1300
NoConn ~ 4650 1800
Text GLabel 6200 4900 2    50   Output ~ 0
KLINE_RX
Text GLabel 6200 5700 2    50   Input ~ 0
KLINE_TX
Text GLabel 7400 5300 0    50   Output ~ 0
KLINE_TX
Text GLabel 7400 5400 0    50   Input ~ 0
KLINE_RX
$Comp
L SparkFun-Resistors:RESISTOR0603 R1
U 1 1 5DE12EEB
P 4450 5000
F 0 "R1" V 4355 5068 45  0000 L CNN
F 1 "1k" V 4439 5068 45  0000 L CNN
F 2 "0603" H 4450 5150 20  0001 C CNN
F 3 "" H 4450 5000 60  0001 C CNN
F 4 " " V 4534 5068 60  0000 L CNN "Field4"
	1    4450 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 4800 4450 4600
Wire Wire Line
	4450 5200 4450 5400
Wire Wire Line
	4450 4600 4700 4600
Wire Wire Line
	3100 3500 3100 4300
Connection ~ 2200 4300
Wire Wire Line
	2200 4300 3100 4300
Wire Wire Line
	4450 5400 4700 5400
Text GLabel 3700 4850 0    50   BiDi ~ 0
KLINE
Text GLabel 3700 5150 0    50   BiDi ~ 0
LLINE
$Comp
L SparkFun-Resistors:RESISTOR0603 R3
U 1 1 5DDEC358
P 3900 5150
F 0 "R3" H 3900 5250 45  0000 C CNN
F 1 "0-DNP" H 3900 5050 45  0000 C CNN
F 2 "0603" H 3900 5300 20  0001 C CNN
F 3 "" H 3900 5150 60  0001 C CNN
F 4 " " H 3900 5029 60  0000 C CNN "Field4"
	1    3900 5150
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R2
U 1 1 5DDF157D
P 3900 4850
F 0 "R2" H 3900 5150 45  0000 C CNN
F 1 "0" H 3900 5066 45  0000 C CNN
F 2 "0603" H 3900 5000 20  0001 C CNN
F 3 "" H 3900 4850 60  0001 C CNN
F 4 " " H 3900 4971 60  0000 C CNN "Field4"
	1    3900 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4850 4300 4850
Wire Wire Line
	4100 5150 4300 5150
Wire Wire Line
	4300 5150 4300 4850
Wire Wire Line
	4300 5150 4300 5400
Wire Wire Line
	4300 5400 4450 5400
Connection ~ 4300 5150
Connection ~ 4450 5400
Wire Wire Line
	4700 5400 4700 5100
Wire Wire Line
	4700 5100 5000 5100
Wire Wire Line
	9250 2100 10350 2100
Wire Wire Line
	10350 2100 10350 2050
Wire Wire Line
	6600 4300 7400 4300
Wire Wire Line
	6600 4200 6600 4150
Wire Wire Line
	6600 4200 7400 4200
$Comp
L SparkFun-LED:LED-RED0603 D1
U 1 1 5E2BCF82
P 4450 2500
F 0 "D1" V 4760 2450 45  0000 C CNN
F 1 "5V" V 4676 2450 45  0000 C CNN
F 2 "LED-0603" V 4250 2500 20  0001 C CNN
F 3 "" H 4450 2500 50  0001 C CNN
F 4 "DIO-00819" V 4581 2450 60  0000 C CNN "Field4"
	1    4450 2500
	0    -1   -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R11
U 1 1 5E2C19AA
P 4900 2500
F 0 "R11" H 4900 2800 45  0000 C CNN
F 1 "1k" H 4900 2716 45  0000 C CNN
F 2 "0603" H 4900 2650 20  0001 C CNN
F 3 "" H 4900 2500 60  0001 C CNN
F 4 " " H 4900 2621 60  0000 C CNN "Field4"
	1    4900 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2500 4700 2500
$Comp
L SparkFun-PowerSymbols:GND #GND0113
U 1 1 5E2CB557
P 5100 3700
F 0 "#GND0113" H 5150 3650 45  0001 L BNN
F 1 "GND" H 5100 3530 45  0000 C CNN
F 2 "" H 5100 3600 60  0001 C CNN
F 3 "" H 5100 3600 60  0001 C CNN
	1    5100 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 3700 5100 3500
$Comp
L SparkFun-LED:LED-RED0603 D3
U 1 1 5E2DB2D0
P 4450 3000
F 0 "D3" V 4760 2950 45  0000 C CNN
F 1 "PWR_EN" V 4676 2950 45  0000 C CNN
F 2 "LED-0603" V 4250 3000 20  0001 C CNN
F 3 "" H 4450 3000 50  0001 C CNN
F 4 "DIO-00819" V 4581 2950 60  0000 C CNN "Field4"
	1    4450 3000
	0    -1   -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R12
U 1 1 5E2DB2D7
P 4900 3000
F 0 "R12" H 4900 3300 45  0000 C CNN
F 1 "2.2k" H 4900 3216 45  0000 C CNN
F 2 "0603" H 4900 3150 20  0001 C CNN
F 3 "" H 4900 3000 60  0001 C CNN
F 4 " " H 4900 3121 60  0000 C CNN "Field4"
	1    4900 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3000 4700 3000
$Comp
L SparkFun-LED:LED-RED0603 D4
U 1 1 5E2DE9AB
P 3000 5450
F 0 "D4" V 3310 5400 45  0000 C CNN
F 1 "KLINE" V 3226 5400 45  0000 C CNN
F 2 "LED-0603" V 2800 5450 20  0001 C CNN
F 3 "" H 3000 5450 50  0001 C CNN
F 4 "DIO-00819" V 3131 5400 60  0000 C CNN "Field4"
	1    3000 5450
	0    -1   -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R13
U 1 1 5E2DE9B2
P 3450 5450
F 0 "R13" H 3450 5750 45  0000 C CNN
F 1 "2,2k" H 3450 5666 45  0000 C CNN
F 2 "0603" H 3450 5600 20  0001 C CNN
F 3 "" H 3450 5450 60  0001 C CNN
F 4 " " H 3450 5571 60  0000 C CNN "Field4"
	1    3450 5450
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 5450 3250 5450
Text GLabel 4350 3000 0    50   Input ~ 0
PWR_EN
Connection ~ 5100 3000
Wire Wire Line
	5100 3000 5100 2500
Connection ~ 5100 3500
Wire Wire Line
	5100 3500 5100 3000
$Comp
L SparkFun-LED:LED-RED0603 D5
U 1 1 5E30C5DB
P 5750 2500
F 0 "D5" V 6060 2450 45  0000 C CNN
F 1 "MCU_D7" V 5976 2450 45  0000 C CNN
F 2 "LED-0603" V 5550 2500 20  0001 C CNN
F 3 "" H 5750 2500 50  0001 C CNN
F 4 "DIO-00819" V 5881 2450 60  0000 C CNN "Field4"
	1    5750 2500
	0    1    -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R14
U 1 1 5E30C5E2
P 5300 2500
F 0 "R14" H 5300 2800 45  0000 C CNN
F 1 "390" H 5300 2716 45  0000 C CNN
F 2 "0603" H 5300 2650 20  0001 C CNN
F 3 "" H 5300 2500 60  0001 C CNN
F 4 " " H 5300 2621 60  0000 C CNN "Field4"
	1    5300 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5550 2500 5500 2500
$Comp
L SparkFun-LED:LED-RED0603 D6
U 1 1 5E30C5EA
P 5750 3000
F 0 "D6" V 6060 2950 45  0000 C CNN
F 1 "MCU_D6" V 5976 2950 45  0000 C CNN
F 2 "LED-0603" V 5550 3000 20  0001 C CNN
F 3 "" H 5750 3000 50  0001 C CNN
F 4 "DIO-00819" V 5881 2950 60  0000 C CNN "Field4"
	1    5750 3000
	0    1    -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R15
U 1 1 5E30C5F1
P 5300 3000
F 0 "R15" H 5300 3300 45  0000 C CNN
F 1 "390" H 5300 3216 45  0000 C CNN
F 2 "0603" H 5300 3150 20  0001 C CNN
F 3 "" H 5300 3000 60  0001 C CNN
F 4 " " H 5300 3121 60  0000 C CNN "Field4"
	1    5300 3000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5550 3000 5500 3000
$Comp
L SparkFun-LED:LED-RED0603 D7
U 1 1 5E30C5F9
P 5750 3500
F 0 "D7" V 6060 3450 45  0000 C CNN
F 1 "GPS_PPS2" V 5976 3450 45  0000 C CNN
F 2 "LED-0603" V 5550 3500 20  0001 C CNN
F 3 "" H 5750 3500 50  0001 C CNN
F 4 "DIO-00819" V 5881 3450 60  0000 C CNN "Field4"
	1    5750 3500
	0    1    -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0603 R16
U 1 1 5E30C600
P 5300 3500
F 0 "R16" H 5300 3800 45  0000 C CNN
F 1 "390" H 5300 3716 45  0000 C CNN
F 2 "0603" H 5300 3650 20  0001 C CNN
F 3 "" H 5300 3500 60  0001 C CNN
F 4 " " H 5300 3621 60  0000 C CNN "Field4"
	1    5300 3500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5550 3500 5500 3500
Text GLabel 5850 2500 2    50   Input ~ 0
LED4
Text GLabel 5850 3000 2    50   Input ~ 0
LED5
Text GLabel 5850 3500 2    50   Input ~ 0
GPS_PPS2
Connection ~ 5100 2500
Wire Wire Line
	3650 5450 4300 5450
Wire Wire Line
	4300 5450 4300 5400
Connection ~ 4300 5400
Text GLabel 7400 3600 0    50   Input ~ 0
GPS_PPS
Text GLabel 7400 3700 0    50   Input ~ 0
GPS_RSTn
Wire Wire Line
	4250 6100 4250 6950
$Comp
L SparkFun-PowerSymbols:5V #SUPPLY0112
U 1 1 5E432CB2
P 4000 2400
F 0 "#SUPPLY0112" H 4050 2400 45  0001 L BNN
F 1 "5V" H 4000 2676 45  0000 C CNN
F 2 "XXX-00000" H 4000 2581 60  0000 C CNN
F 3 "" H 4000 2400 60  0001 C CNN
	1    4000 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2400 4000 2500
Wire Wire Line
	4000 2500 4350 2500
Text GLabel 7400 3500 0    50   Output ~ 0
LED4
Text GLabel 7400 3400 0    50   Output ~ 0
LED5
Text Notes 9350 6250 0    50   ~ 0
Internal PD\n
Text Notes 2900 6150 0    50   ~ 0
5V, 3A
$Comp
L dk_Coaxial-Connectors-RF:142-0701-801 J3
U 1 1 5DF07947
P 3100 3300
F 0 "J3" H 3012 3268 50  0000 R CNN
F 1 "142-0701-801" H 3012 3177 50  0000 R CNN
F 2 "digikey-footprints:RF_SMA_BoardEdge_142-0701-801" H 3300 3500 60  0001 L CNN
F 3 "http://www.belfuse.com/resources/Johnson/drawings/dr-1420701801.pdf" H 3300 3600 60  0001 L CNN
F 4 "J502-ND" H 3300 3700 60  0001 L CNN "Digi-Key_PN"
F 5 "142-0701-801" H 3300 3800 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 3300 3900 60  0001 L CNN "Category"
F 7 "Coaxial Connectors (RF)" H 3300 4000 60  0001 L CNN "Family"
F 8 "http://www.belfuse.com/resources/Johnson/drawings/dr-1420701801.pdf" H 3300 4100 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cinch-connectivity-solutions-johnson/142-0701-801/J502-ND/35280" H 3300 4200 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN SMA JACK STR 50OHM EDGE MNT" H 3300 4300 60  0001 L CNN "Description"
F 11 "Cinch Connectivity Solutions Johnson" H 3300 4400 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3300 4500 60  0001 L CNN "Status"
	1    3100 3300
	-1   0    0    -1  
$EndComp
Text GLabel 7400 5000 0    50   Output ~ 0
MCU_TX4
Text GLabel 7400 4900 0    50   Input ~ 0
MCU_RX4
$Comp
L Connector:Conn_01x14_Male J2
U 1 1 5E5F1E9F
P 9050 1400
F 0 "J2" H 9158 2181 50  0000 C CNN
F 1 "Conn_01x14_Male" H 9200 600 50  0000 C CNN
F 2 "Connector_Molex:Molex_PicoBlade_53048-1410_1x14_P1.25mm_Horizontal" H 9050 1400 50  0001 C CNN
F 3 "~" H 9050 1400 50  0001 C CNN
	1    9050 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J4
U 1 1 5E5F38A9
P 10850 2800
F 0 "J4" H 10822 2774 50  0000 R CNN
F 1 "Conn_01x08_Male" H 11400 2250 50  0000 R CNN
F 2 "Connector_Molex:Molex_PicoBlade_53047-0810_1x08_P1.25mm_Vertical" H 10850 2800 50  0001 C CNN
F 3 "~" H 10850 2800 50  0001 C CNN
	1    10850 2800
	-1   0    0    -1  
$EndComp
Text GLabel 9250 1500 2    50   Input ~ 0
MCU_TX4
Text GLabel 9250 1400 2    50   Output ~ 0
MCU_RX4
Text GLabel 7400 5100 0    50   BiDi ~ 0
MCU_SDA0
Text GLabel 7400 5200 0    50   BiDi ~ 0
MCU_SCL0
$Comp
L SparkFun-PowerSymbols:GND #GND0114
U 1 1 5E67C1DF
P 10100 2550
F 0 "#GND0114" H 10150 2500 45  0001 L BNN
F 1 "GND" H 10100 2380 45  0000 C CNN
F 2 "" H 10100 2450 60  0001 C CNN
F 3 "" H 10100 2450 60  0001 C CNN
	1    10100 2550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10650 2600 10550 2600
Wire Wire Line
	10550 2600 10550 2500
Connection ~ 10550 2500
Wire Wire Line
	10550 2500 10650 2500
Wire Wire Line
	10100 2500 10100 2550
Wire Wire Line
	10100 2500 10550 2500
Text GLabel 9250 1900 2    50   BiDi ~ 0
MCU_SDA0
Text GLabel 9250 2000 2    50   BiDi ~ 0
MCU_SCL0
Wire Wire Line
	9250 1700 9650 1700
Wire Wire Line
	10350 1700 10350 1600
Wire Wire Line
	9250 1800 9650 1800
Wire Wire Line
	9650 1800 9650 1700
Connection ~ 9650 1700
Wire Wire Line
	9650 1700 10350 1700
Wire Wire Line
	9250 800  9650 800 
Wire Wire Line
	9250 900  9650 900 
Wire Wire Line
	9650 900  9650 800 
Connection ~ 9650 800 
Wire Wire Line
	9650 800  10350 800 
Text GLabel 10650 3100 0    50   Input ~ 0
MCU_TX4
Text GLabel 10650 3200 0    50   Output ~ 0
MCU_RX4
Text GLabel 10650 2800 0    50   BiDi ~ 0
MCU_SDA0
Text GLabel 10650 2700 0    50   BiDi ~ 0
MCU_SCL0
$Comp
L SparkFun-PowerSymbols:5V #SUPPLY0113
U 1 1 5E76524D
P 10050 3100
F 0 "#SUPPLY0113" H 10100 3100 45  0001 L BNN
F 1 "5V" H 10050 3376 45  0000 C CNN
F 2 "XXX-00000" H 10050 3281 60  0000 C CNN
F 3 "" H 10050 3100 60  0001 C CNN
	1    10050 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 3000 10450 3000
Wire Wire Line
	10150 3000 10150 3100
Wire Wire Line
	10150 3100 10050 3100
Wire Wire Line
	10650 2900 10450 2900
Wire Wire Line
	10450 2900 10450 3000
Connection ~ 10450 3000
Wire Wire Line
	10450 3000 10150 3000
Wire Wire Line
	4700 4600 4700 4500
$Comp
L SparkFun-PowerSymbols:V_BATT #SUPPLY0101
U 1 1 5DDFDC95
P 4700 4500
F 0 "#SUPPLY0101" H 4750 4500 45  0001 L BNN
F 1 "V_BATT" H 4700 4776 45  0000 C CNN
F 2 "XXX-00000" H 4700 4681 60  0000 C CNN
F 3 "" H 4700 4500 60  0001 C CNN
	1    4700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5450 2400 5350
$Comp
L SparkFun-PowerSymbols:V_BATT #SUPPLY0114
U 1 1 5E800426
P 2400 5350
F 0 "#SUPPLY0114" H 2450 5350 45  0001 L BNN
F 1 "V_BATT" H 2400 5626 45  0000 C CNN
F 2 "XXX-00000" H 2400 5531 60  0000 C CNN
F 3 "" H 2400 5350 60  0001 C CNN
	1    2400 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5450 2900 5450
NoConn ~ 7400 3200
NoConn ~ 7400 3300
NoConn ~ 2000 2300
NoConn ~ 1100 2600
NoConn ~ 1100 2700
NoConn ~ 1100 3200
NoConn ~ 1100 3300
NoConn ~ 1100 3500
NoConn ~ 1100 3600
NoConn ~ 1100 4000
NoConn ~ 2500 3100
$Comp
L Device:Battery_Cell BT?
U 1 1 5E8EA43B
P 2800 2000
F 0 "BT?" V 3055 2050 50  0000 C CNN
F 1 "Battery_Cell" V 2964 2050 50  0000 C CNN
F 2 "Battery:BatteryHolder_Keystone_3000_1x12mm" V 2800 2060 50  0001 C CNN
F 3 "~" V 2800 2060 50  0001 C CNN
	1    2800 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1700 2000 2600 2000
$EndSCHEMATC
