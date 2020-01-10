/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This file was generated by cantools version 32.21.0 Tue Dec 17 19:20:22 2019.
 */

#include <string.h>

#include "subaru_hscan.h"

static inline uint8_t pack_left_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_right_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint16_t unpack_left_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) << shift);
}

static inline uint8_t unpack_right_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value & mask) >> shift);
}

static inline uint16_t unpack_right_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) >> shift);
}

int subaru_hscan_body_stat_2_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_body_stat_2_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[1] |= pack_left_shift_u16(src_p->fuel_consumption, 0u, 0xffu);
    dst_p[2] |= pack_right_shift_u16(src_p->fuel_consumption, 8u, 0xffu);
    dst_p[3] |= pack_left_shift_u8(src_p->temp_coolant, 0u, 0xffu);
    dst_p[6] |= pack_left_shift_u8(src_p->clutch_sw, 2u, 0x04u);

    return (8);
}

int subaru_hscan_body_stat_2_unpack(
    struct subaru_hscan_body_stat_2_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->fuel_consumption |= unpack_right_shift_u16(src_p[1], 0u, 0xffu);
    dst_p->fuel_consumption |= unpack_left_shift_u16(src_p[2], 8u, 0xffu);
    dst_p->temp_coolant |= unpack_right_shift_u8(src_p[3], 0u, 0xffu);
    dst_p->clutch_sw |= unpack_right_shift_u8(src_p[6], 2u, 0x04u);

    return (0);
}

uint16_t subaru_hscan_body_stat_2_fuel_consumption_encode(double value)
{
    return (uint16_t)(value);
}

double subaru_hscan_body_stat_2_fuel_consumption_decode(uint16_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_2_fuel_consumption_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_body_stat_2_temp_coolant_encode(double value)
{
    return (uint8_t)(value - -40.0);
}

double subaru_hscan_body_stat_2_temp_coolant_decode(uint8_t value)
{
    return ((double)value + -40.0);
}

bool subaru_hscan_body_stat_2_temp_coolant_is_in_range(uint8_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_body_stat_2_clutch_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_body_stat_2_clutch_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_2_clutch_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int subaru_hscan_body_stat_1_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_body_stat_1_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[0] |= pack_left_shift_u8(src_p->reverse_sw, 2u, 0x04u);
    dst_p[2] |= pack_left_shift_u8(src_p->temp_out, 0u, 0xffu);
    dst_p[3] |= pack_left_shift_u8(src_p->drl_sw, 1u, 0x02u);
    dst_p[3] |= pack_left_shift_u8(src_p->headlight_sw, 2u, 0x04u);
    dst_p[3] |= pack_left_shift_u8(src_p->bright_sw, 3u, 0x08u);
    dst_p[3] |= pack_left_shift_u8(src_p->wiper_sw, 6u, 0x40u);
    dst_p[4] |= pack_left_shift_u16(src_p->fuel_res, 6u, 0xc0u);
    dst_p[5] |= pack_right_shift_u16(src_p->fuel_res, 2u, 0xffu);
    dst_p[7] |= pack_left_shift_u8(src_p->handbrake_sw, 7u, 0x80u);

    return (8);
}

int subaru_hscan_body_stat_1_unpack(
    struct subaru_hscan_body_stat_1_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->reverse_sw |= unpack_right_shift_u8(src_p[0], 2u, 0x04u);
    dst_p->temp_out |= unpack_right_shift_u8(src_p[2], 0u, 0xffu);
    dst_p->drl_sw |= unpack_right_shift_u8(src_p[3], 1u, 0x02u);
    dst_p->headlight_sw |= unpack_right_shift_u8(src_p[3], 2u, 0x04u);
    dst_p->bright_sw |= unpack_right_shift_u8(src_p[3], 3u, 0x08u);
    dst_p->wiper_sw |= unpack_right_shift_u8(src_p[3], 6u, 0x40u);
    dst_p->fuel_res |= unpack_right_shift_u16(src_p[4], 6u, 0xc0u);
    dst_p->fuel_res |= unpack_left_shift_u16(src_p[5], 2u, 0xffu);
    dst_p->handbrake_sw |= unpack_right_shift_u8(src_p[7], 7u, 0x80u);

    return (0);
}

uint8_t subaru_hscan_body_stat_1_reverse_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_body_stat_1_reverse_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_1_reverse_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t subaru_hscan_body_stat_1_temp_out_encode(double value)
{
    return (uint8_t)((value - -40.0) / 0.5);
}

double subaru_hscan_body_stat_1_temp_out_decode(uint8_t value)
{
    return (((double)value * 0.5) + -40.0);
}

bool subaru_hscan_body_stat_1_temp_out_is_in_range(uint8_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_body_stat_1_drl_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_body_stat_1_drl_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_1_drl_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t subaru_hscan_body_stat_1_headlight_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_body_stat_1_headlight_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_1_headlight_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t subaru_hscan_body_stat_1_bright_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_body_stat_1_bright_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_1_bright_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t subaru_hscan_body_stat_1_wiper_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_body_stat_1_wiper_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_1_wiper_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint16_t subaru_hscan_body_stat_1_fuel_res_encode(double value)
{
    return (uint16_t)(value / 0.1);
}

double subaru_hscan_body_stat_1_fuel_res_decode(uint16_t value)
{
    return ((double)value * 0.1);
}

bool subaru_hscan_body_stat_1_fuel_res_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_body_stat_1_handbrake_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_body_stat_1_handbrake_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_body_stat_1_handbrake_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int subaru_hscan_wheel_speed_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_wheel_speed_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[0] |= pack_left_shift_u16(src_p->wss_fl, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u16(src_p->wss_fl, 8u, 0xffu);
    dst_p[2] |= pack_left_shift_u16(src_p->wss_fr, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(src_p->wss_fr, 8u, 0xffu);
    dst_p[4] |= pack_left_shift_u16(src_p->wss_rl, 0u, 0xffu);
    dst_p[5] |= pack_right_shift_u16(src_p->wss_rl, 8u, 0xffu);
    dst_p[6] |= pack_left_shift_u16(src_p->wss_rr, 0u, 0xffu);
    dst_p[7] |= pack_right_shift_u16(src_p->wss_rr, 8u, 0xffu);

    return (8);
}

int subaru_hscan_wheel_speed_unpack(
    struct subaru_hscan_wheel_speed_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->wss_fl |= unpack_right_shift_u16(src_p[0], 0u, 0xffu);
    dst_p->wss_fl |= unpack_left_shift_u16(src_p[1], 8u, 0xffu);
    dst_p->wss_fr |= unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    dst_p->wss_fr |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->wss_rl |= unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    dst_p->wss_rl |= unpack_left_shift_u16(src_p[5], 8u, 0xffu);
    dst_p->wss_rr |= unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    dst_p->wss_rr |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);

    return (0);
}

uint16_t subaru_hscan_wheel_speed_wss_fl_encode(double value)
{
    return (uint16_t)(value / 0.05625);
}

double subaru_hscan_wheel_speed_wss_fl_decode(uint16_t value)
{
    return ((double)value * 0.05625);
}

bool subaru_hscan_wheel_speed_wss_fl_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

uint16_t subaru_hscan_wheel_speed_wss_fr_encode(double value)
{
    return (uint16_t)(value / 0.05625);
}

double subaru_hscan_wheel_speed_wss_fr_decode(uint16_t value)
{
    return ((double)value * 0.05625);
}

bool subaru_hscan_wheel_speed_wss_fr_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

uint16_t subaru_hscan_wheel_speed_wss_rl_encode(double value)
{
    return (uint16_t)(value / 0.05625);
}

double subaru_hscan_wheel_speed_wss_rl_decode(uint16_t value)
{
    return ((double)value * 0.05625);
}

bool subaru_hscan_wheel_speed_wss_rl_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

uint16_t subaru_hscan_wheel_speed_wss_rr_encode(double value)
{
    return (uint16_t)(value / 0.05625);
}

double subaru_hscan_wheel_speed_wss_rr_decode(uint16_t value)
{
    return ((double)value * 0.05625);
}

bool subaru_hscan_wheel_speed_wss_rr_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

int subaru_hscan_speed_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_speed_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[0] |= pack_left_shift_u8(src_p->esp_sw, 4u, 0x10u);
    dst_p[2] |= pack_left_shift_u16(src_p->veh_speed, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(src_p->veh_speed, 8u, 0xffu);
    dst_p[4] |= pack_left_shift_u8(src_p->brake_sw, 4u, 0x10u);

    return (8);
}

int subaru_hscan_speed_unpack(
    struct subaru_hscan_speed_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->esp_sw |= unpack_right_shift_u8(src_p[0], 4u, 0x10u);
    dst_p->veh_speed |= unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    dst_p->veh_speed |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->brake_sw |= unpack_right_shift_u8(src_p[4], 4u, 0x10u);

    return (0);
}

uint8_t subaru_hscan_speed_esp_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_speed_esp_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_speed_esp_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint16_t subaru_hscan_speed_veh_speed_encode(double value)
{
    return (uint16_t)(value / 0.05625);
}

double subaru_hscan_speed_veh_speed_decode(uint16_t value)
{
    return ((double)value * 0.05625);
}

bool subaru_hscan_speed_veh_speed_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_speed_brake_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_speed_brake_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_speed_brake_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int subaru_hscan_driver_input_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_driver_input_t *src_p,
    size_t size)
{
    uint16_t steering_angle;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    steering_angle = (uint16_t)src_p->steering_angle;
    dst_p[0] |= pack_left_shift_u16(steering_angle, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u16(steering_angle, 8u, 0xffu);
    dst_p[4] |= pack_left_shift_u8(src_p->brake_pos, 0u, 0xffu);

    return (8);
}

int subaru_hscan_driver_input_unpack(
    struct subaru_hscan_driver_input_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t steering_angle;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    steering_angle = 0u;
    steering_angle |= unpack_right_shift_u16(src_p[0], 0u, 0xffu);
    steering_angle |= unpack_left_shift_u16(src_p[1], 8u, 0xffu);
    dst_p->steering_angle = (int16_t)steering_angle;
    dst_p->brake_pos |= unpack_right_shift_u8(src_p[4], 0u, 0xffu);

    return (0);
}

int16_t subaru_hscan_driver_input_steering_angle_encode(double value)
{
    return (int16_t)(value);
}

double subaru_hscan_driver_input_steering_angle_decode(int16_t value)
{
    return ((double)value);
}

bool subaru_hscan_driver_input_steering_angle_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_driver_input_brake_pos_encode(double value)
{
    return (uint8_t)(value / 0.392156862745098);
}

double subaru_hscan_driver_input_brake_pos_decode(uint8_t value)
{
    return ((double)value * 0.392156862745098);
}

bool subaru_hscan_driver_input_brake_pos_is_in_range(uint8_t value)
{
    (void)value;

    return (true);
}

int subaru_hscan_ecu_status_2_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_ecu_status_2_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[4] |= pack_left_shift_u8(src_p->gear, 0u, 0xffu);
    dst_p[5] |= pack_left_shift_u8(src_p->cruise_speed, 0u, 0xffu);
    dst_p[6] |= pack_left_shift_u8(src_p->brake_sw_1, 4u, 0x10u);
    dst_p[6] |= pack_left_shift_u8(src_p->cruise_cruise, 6u, 0x40u);
    dst_p[6] |= pack_left_shift_u8(src_p->cruise_set, 7u, 0x80u);
    dst_p[7] |= pack_left_shift_u8(src_p->mil_sw, 0u, 0x01u);

    return (8);
}

int subaru_hscan_ecu_status_2_unpack(
    struct subaru_hscan_ecu_status_2_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->gear |= unpack_right_shift_u8(src_p[4], 0u, 0xffu);
    dst_p->cruise_speed |= unpack_right_shift_u8(src_p[5], 0u, 0xffu);
    dst_p->brake_sw_1 |= unpack_right_shift_u8(src_p[6], 4u, 0x10u);
    dst_p->cruise_cruise |= unpack_right_shift_u8(src_p[6], 6u, 0x40u);
    dst_p->cruise_set |= unpack_right_shift_u8(src_p[6], 7u, 0x80u);
    dst_p->mil_sw |= unpack_right_shift_u8(src_p[7], 0u, 0x01u);

    return (0);
}

uint8_t subaru_hscan_ecu_status_2_gear_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_ecu_status_2_gear_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_2_gear_is_in_range(uint8_t value)
{
    return (value <= 6u);
}

uint8_t subaru_hscan_ecu_status_2_cruise_speed_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_ecu_status_2_cruise_speed_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_2_cruise_speed_is_in_range(uint8_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_ecu_status_2_brake_sw_1_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_ecu_status_2_brake_sw_1_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_2_brake_sw_1_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t subaru_hscan_ecu_status_2_cruise_cruise_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_ecu_status_2_cruise_cruise_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_2_cruise_cruise_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t subaru_hscan_ecu_status_2_cruise_set_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_ecu_status_2_cruise_set_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_2_cruise_set_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t subaru_hscan_ecu_status_2_mil_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_ecu_status_2_mil_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_2_mil_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int subaru_hscan_ecu_status_1_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_ecu_status_1_t *src_p,
    size_t size)
{
    uint8_t eng_tq;
    uint8_t trans_tq;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    trans_tq = (uint8_t)src_p->trans_tq;
    dst_p[1] |= pack_left_shift_u8(trans_tq, 0u, 0xffu);
    eng_tq = (uint8_t)src_p->eng_tq;
    dst_p[2] |= pack_left_shift_u8(eng_tq, 0u, 0xffu);
    dst_p[3] |= pack_left_shift_u8(src_p->loss_tq, 0u, 0xffu);
    dst_p[4] |= pack_left_shift_u8(src_p->accel_pos, 0u, 0xffu);
    dst_p[5] |= pack_left_shift_u16(src_p->engine_speed, 0u, 0xffu);
    dst_p[6] |= pack_right_shift_u16(src_p->engine_speed, 8u, 0xffu);
    dst_p[7] |= pack_left_shift_u8(src_p->compressor_sw, 2u, 0x04u);

    return (8);
}

int subaru_hscan_ecu_status_1_unpack(
    struct subaru_hscan_ecu_status_1_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint8_t eng_tq;
    uint8_t trans_tq;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    trans_tq = 0u;
    trans_tq |= unpack_right_shift_u8(src_p[1], 0u, 0xffu);
    dst_p->trans_tq = (int8_t)trans_tq;
    eng_tq = 0u;
    eng_tq |= unpack_right_shift_u8(src_p[2], 0u, 0xffu);
    dst_p->eng_tq = (int8_t)eng_tq;
    dst_p->loss_tq |= unpack_right_shift_u8(src_p[3], 0u, 0xffu);
    dst_p->accel_pos |= unpack_right_shift_u8(src_p[4], 0u, 0xffu);
    dst_p->engine_speed |= unpack_right_shift_u16(src_p[5], 0u, 0xffu);
    dst_p->engine_speed |= unpack_left_shift_u16(src_p[6], 8u, 0xffu);
    dst_p->compressor_sw |= unpack_right_shift_u8(src_p[7], 2u, 0x04u);

    return (0);
}

int8_t subaru_hscan_ecu_status_1_trans_tq_encode(double value)
{
    return (int8_t)(value / 1.6);
}

double subaru_hscan_ecu_status_1_trans_tq_decode(int8_t value)
{
    return ((double)value * 1.6);
}

bool subaru_hscan_ecu_status_1_trans_tq_is_in_range(int8_t value)
{
    (void)value;

    return (true);
}

int8_t subaru_hscan_ecu_status_1_eng_tq_encode(double value)
{
    return (int8_t)(value / 1.6);
}

double subaru_hscan_ecu_status_1_eng_tq_decode(int8_t value)
{
    return ((double)value * 1.6);
}

bool subaru_hscan_ecu_status_1_eng_tq_is_in_range(int8_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_ecu_status_1_loss_tq_encode(double value)
{
    return (uint8_t)(value / 1.6);
}

double subaru_hscan_ecu_status_1_loss_tq_decode(uint8_t value)
{
    return ((double)value * 1.6);
}

bool subaru_hscan_ecu_status_1_loss_tq_is_in_range(uint8_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_ecu_status_1_accel_pos_encode(double value)
{
    return (uint8_t)(value / 0.392156862745098);
}

double subaru_hscan_ecu_status_1_accel_pos_decode(uint8_t value)
{
    return ((double)value * 0.392156862745098);
}

bool subaru_hscan_ecu_status_1_accel_pos_is_in_range(uint8_t value)
{
    (void)value;

    return (true);
}

uint16_t subaru_hscan_ecu_status_1_engine_speed_encode(double value)
{
    return (uint16_t)(value);
}

double subaru_hscan_ecu_status_1_engine_speed_decode(uint16_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_1_engine_speed_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

uint8_t subaru_hscan_ecu_status_1_compressor_sw_encode(double value)
{
    return (uint8_t)(value);
}

double subaru_hscan_ecu_status_1_compressor_sw_decode(uint8_t value)
{
    return ((double)value);
}

bool subaru_hscan_ecu_status_1_compressor_sw_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int subaru_hscan_steering_sensor_status_pack(
    uint8_t *dst_p,
    const struct subaru_hscan_steering_sensor_status_t *src_p,
    size_t size)
{
    (void)src_p;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    return (8);
}

int subaru_hscan_steering_sensor_status_unpack(
    struct subaru_hscan_steering_sensor_status_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    (void)src_p;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    return (0);
}
