#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* --- RP2350 / Cortex-M33 核心特定設定 --- */
#define configENABLE_FPU                 1    /* RP2350 有硬體浮點運算，建議開 1 */
#define configENABLE_MPU                 0    /* 暫時關閉記憶體保護單元 */
#define configENABLE_TRUSTZONE           0    /* 暫時關閉 TrustZone 以簡化開發 */
#define configRUN_FREERTOS_SECURE_ONLY   1    /* 強制跑在非安全模式 (標準做法) */

/* 修正 vTaskCoreAffinitySet 警告 */
#define configUSE_CORE_AFFINITY          1    /* 必須開啟這個，API 才會被宣告 */

/* 剛才新增的自旋鎖 */
#define configSMP_SPINLOCK_0            0
#define configSMP_SPINLOCK_1            1

/* 修正 event_groups.c 編譯錯誤 */
#define portTIMER_CALLBACK_ATTRIBUTE

/* 中斷與語法修正 */
#define portTIMER_CALLBACK_ATTRIBUTE
#ifndef SIO_IRQ_PROC0
    #define SIO_IRQ_PROC0               0 // 修正點
#endif

/* 核心硬體設定 */
#define configPTRDIFF_TYPE              intptr_t
#define configSIZE_T                    size_t
#define configCPU_CLOCK_HZ              150000000UL /* RP2350 預設時脈 */
#define configTICK_RATE_HZ              ((TickType_t)1000)
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 64 * 1024 ) ) // 修正點

/* --- SMP (雙核心) 關鍵設定 --- */
#define configNUMBER_OF_CORES           2           /* 啟用雙核心 */
#define configTICK_CORE                 0           /* 由 Core 0 處理系統心跳 */
#define configRUN_MULTIPLE_PRIORITIES   1           /* 允許不同核心跑不同優先級任務 */
#define configUSE_PASSIVE_IDLE_HOOK      0

/* 記憶體與排程管理 */
#define configMAX_PRIORITIES            32
#define configMINIMAL_STACK_SIZE        (configSTACK_DEPTH_TYPE)256
#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configUSE_16_BIT_TICKS          0
#define configSUPPORT_DYNAMIC_ALLOCATION 1

/* 常用功能啟用 */
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_COUNTING_SEMAPHORES   1
#define configUSE_QUEUE_SETS            1

/* 斷言 (Debug 必備) */
extern void vApplicationAssert( const char *pcFileName, uint32_t ulLine );
#define configASSERT( x ) if( ( x ) == 0 ) vApplicationAssert( __FILE__, __LINE__ )

/* API 映射 */
#define INCLUDE_vTaskPrioritySet             1
#define INCLUDE_uxTaskPriorityGet            1
#define INCLUDE_vTaskDelete                  1
#define INCLUDE_vTaskSuspend                 1
#define INCLUDE_vTaskDelayUntil              1
#define INCLUDE_vTaskDelay                   1
#define INCLUDE_xTaskGetSchedulerState       1
#define INCLUDE_xTaskGetCurrentTaskHandle    1

#endif /* FREERTOS_CONFIG_H */
