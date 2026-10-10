#ifndef GROVE_SERVO_H
#define GROVE_SERVO_H

#include "pico/stdlib.h"

// 初始化 GPIO 作為 Servo 輸出
void grove_servo_init(uint gpio);

// 設定絕對角度 (0 ~ 180 度)
void grove_servo_set_angle(uint gpio, float angle);

void servo_test(uint gpio, uint max_us_pwm, uint min_us_pwm);

#endif // GROVE_SERVO_H
