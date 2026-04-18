#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

// 簡單的 LED 閃爍任務 (鎖定在 Core 0)
void led_task(void *pvParameters) {
    const uint LED_PIN = 25; // 注意：Pico 2 W 的 LED 可能需要透過 Wi-Fi 晶片控制，此處僅供編譯測試
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        printf("Task 1 (Core 0) is running...\n");
        gpio_put(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_put(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// 串口輸出任務 (鎖定在 Core 1)
void hello_task(void *pvParameters) {
    while (true) {
        printf("Task 2 (Core 1) is waving hello!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// 斷言實作 (避免編譯錯誤)
void vApplicationAssert(const char *pcFileName, uint32_t ulLine) {
    printf("ASSERT Failed: %s, line %u\n", pcFileName, (unsigned int)ulLine);
    while (1);
}

int main() {
    stdio_init_all();
    printf("RP2350 FreeRTOS SMP Dual-Core Demo Starting...\n");

    // 建立 Task 1
    TaskHandle_t xLedTaskHandle;
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, &xLedTaskHandle);
    vTaskCoreAffinitySet(xLedTaskHandle, (1 << 0)); // 鎖定在 Core 0

    // 建立 Task 2
    TaskHandle_t xHelloTaskHandle;
    xTaskCreate(hello_task, "Hello_Task", 256, NULL, 1, &xHelloTaskHandle);
    vTaskCoreAffinitySet(xHelloTaskHandle, (1 << 1)); // 鎖定在 Core 1

    // 啟動排程器 (在 SMP 模式下，這會同時啟動兩個核心)
    vTaskStartScheduler();

    while (1); // 永遠不該執行到這
}
