#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

/* --- 修正 SMP Linker 錯誤的誘餌 --- */
//extern TaskHandle_t volatile pxCurrentTCBs[ configNUMBER_OF_CORES ];
//TaskHandle_t volatile pxCurrentTCB = NULL;
#include <stdio.h>
#include "pico/stdlib.h"

void vApplicationAssert( const char *pcFileName, uint32_t ulLine ) {
    printf("ASSERT Failed at %s:%ld\n", pcFileName, ulLine);
    while (1) {
        __breakpoint(); 
    }
}

// 任務：只負責印字
void vUsbPrintTask(void *pvParameters) {
    (void) pvParameters;
    int count = 0;
    while (1) {
        printf("Pico 2 WH SMP: Running... Msg #%d\n", count++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// 串口輸出任務 (鎖定在 Core 1)
void hello_task(void *pvParameters) {
    while (true) {
        printf("Task 2 (Core 1) is waving hello!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main() {
    
    TaskHandle_t xCore0TaskHandle, xCore1TaskHandle;
    xCore0TaskHandle = NULL;
    xCore1TaskHandle = NULL;
    // 1. 初始化所有標準輸出 (包含 USB)
    stdio_init_all();

    // 2. 進入一個純 SDK 的死迴圈，完全不啟動 FreeRTOS
    //while (1) {
    //    printf("Pico 2 WH: Native SDK USB Running...\n");
    //    sleep_ms(1000);
    //}
    // 2. 給 USB 5 秒鐘 (加長一點)，讓 Windows 慢慢抓 Descriptor
    for(int i=0; i<5; i++) {
        sleep_ms(1000);
    }

    // 3. 建立任務
    xTaskCreate(vUsbPrintTask, "USB_Task", 1024, NULL, 1, &xCore0TaskHandle);
    vTaskCoreAffinitySet(xCore0TaskHandle, (1 << 0)); // 鎖定在 Core 0
						    
    xTaskCreate(hello_task, "Hello_Task", 256, NULL, 1, &xCore1TaskHandle);
    vTaskCoreAffinitySet(xCore1TaskHandle, (1 << 1)); // 鎖定在 Core 1

    
    // 🔥 關鍵同步
    //pxCurrentTCB = pxCurrentTCBs[0];

    // 4. 啟動排程
    vTaskStartScheduler();

    return 0;
}

/*
// 簡易 Assert 實作 (不操作 LED)
void vApplicationAssert( const char *pcFileName, uint32_t ulLine ) {
    // 如果掛掉，就在這裡死迴圈，不做任何硬體動作
    while (1) {
        __breakpoint(); 
    }
}

int main() {
    stdio_init_all();
    sleep_ms(5000); 

    // 建議補回任務，否則你無法判斷 USB 是「活著但沒話說」還是「死掉了」
    xTaskCreate(vUsbPrintTask, "USB_Task", 1024, NULL, 1, NULL);
    
    vTaskStartScheduler(); 
    while(1);
}
int main() {
    // 1. 只初始化基礎 stdio (包含 USB)
    stdio_init_all();

    // 2. 給 USB 5 秒鐘 (加長一點)，讓 Windows 慢慢抓 Descriptor
    for(int i=0; i<5; i++) {
        sleep_ms(1000);
    }

    // 3. 建立任務
    xTaskCreate(vUsbPrintTask, "USB_Task", 1024, NULL, 1, NULL);

    // 🔥 關鍵同步
    pxCurrentTCB = pxCurrentTCBs[0]; 

    // 4. 啟動排程
    vTaskStartScheduler();
    
    while (1);
}*/
