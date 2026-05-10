#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* --- Pico SDK 整合 --- */
#include "pico/stdlib.h"

/* 基礎設定 */
#define configUSE_PREEMPTION                    1
#define configUSE_TICKLESS_IDLE                 0
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCPU_CLOCK_HZ                      150000000UL
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES                    32
#define configMINIMAL_STACK_SIZE                ( configSTACK_DEPTH_TYPE ) 512
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               8
#define configUSE_QUEUE_SETS                    1

/* 記憶體管理 */
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 128 * 1024 ) )

/* 斷言與除錯 */
extern void vApplicationAssert( const char *pcFileName, uint32_t ulLine );
#define configASSERT( x ) if( ( x ) == 0 ) vApplicationAssert( __FILE__, __LINE__ )

/* --- RP2350 (Cortex-M33) 特定設定 --- */
#define configPRIO_BITS                         3
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY      0x07
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 0x05

#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

/* FPU 與架構設定 (RP2350 必備) */
#define configENABLE_FPU                        1
#define configENABLE_MPU                        0
#define configENABLE_TRUSTZONE                  0
#define configRUN_FREERTOS_SECURE_ONLY          1

/* --- 多核 (SMP) 設定 --- */
/* 建議先用單核跑通 USB，確認沒問題後再將以下改為 2 */
#define configNUMBER_OF_CORES                   2 
#define configTICK_CORE                         0
#define configRUN_MULTIPLE_PRIORITIES           1
#define configUSE_CORE_AFFINITY                 1

/* * 定義 FreeRTOS SMP 使用的硬體自旋鎖編號
 * 選擇 16 和 17 是為了避開 SDK 內部佔用的低編號鎖 (0-15)
 */
#define configSMP_SPINLOCK_0             16
#define configSMP_SPINLOCK_1             17

/* * 核心間通訊 (IPI) 使用的門鈴中斷
 * RP2350 預設通常使用 16 
 */
#define configSOFT_INTERRUPT_VECTOR      16

/* 官方版 Port 需要這個來對接 SDK 的 Spinlock */
#define configUSE_PASSIVE_IDLE_HOOK             0

/* API 映射 */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_xTaskCoreAffinitySet            1

#endif /* FREERTOS_CONFIG_H */
