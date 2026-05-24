#include "grove_servo.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define SERVO_MIN_PULSE_US   1000   // 0 度 = 1000us
#define SERVO_MAX_PULSE_US   2000   // 180 度 = 2000us
#define PWM_PERIOD_US        20000  // 50Hz = 20000us (20ms)

static uint slice_num;
static uint channel;

void grove_servo_init(uint gpio) {
    // 1. 設定 GPIO 功能為 PWM
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    
    // 2. 取得該 GPIO 對應的 PWM Slice 與 Channel
    slice_num = pwm_gpio_to_slice_num(gpio);
    channel = pwm_gpio_to_channel(gpio);
    
    // 3. 計算分頻優化計數器
    // RP2350 預設系統時鐘為 150MHz。我們希望 1MHz 的計數頻率 (1us/tick)
    // Clock Config: 150,000,000 / 1,000,000 = 150.0f
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 150.0f); 
    
    // 4. 設定計數器週期 (Wrap 值)，達到 20ms 週期
    pwm_config_set_wrap(&config, PWM_PERIOD_US - 1);
    
    // 5. 將配置寫入硬體暫存器並啟動 PWM
    pwm_init(slice_num, &config, true);
}

void grove_servo_set_angle(uint gpio, float angle) {
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;
    
    // 將角度線性轉換為脈衝寬度 (1000us ~ 2000us)
    uint32_t pulse_width = SERVO_MIN_PULSE_US + (uint32_t)((angle / 180.0f) * (SERVO_MAX_PULSE_US - SERVO_MIN_PULSE_US));
    
    // 實時寫入硬體比較暫存器 (CC Register)
    pwm_set_chan_level(pwm_gpio_to_slice_num(gpio), pwm_gpio_to_channel(gpio), pulse_width);
}
