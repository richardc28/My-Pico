#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* --- RP2350 多核硬體對接 --- */
#include "pico/multicore.h"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/sio.h"

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

/* 確保使用了正確的匯編指令集 */
#define configENABLE_FPU    1

/* 針對 RP2350-ARM-S 模式，這兩行能解決 "conflicting architectures" 的隱性衝突 */
#ifndef __ARM_ARCH_8M_MAIN__
    #define __ARM_ARCH_8M_MAIN__ 1
#endif

/* 修正 event_groups.c 編譯錯誤 */
#define portTIMER_CALLBACK_ATTRIBUTE

/* 中斷與語法修正 */
#define portTIMER_CALLBACK_ATTRIBUTE
#ifndef SIO_IRQ_PROC0
    #define SIO_IRQ_PROC0               26 // 修正點
#endif

/* 核心硬體設定 */
#define configCPU_CLOCK_HZ          150000000UL 
#define configMINIMAL_STACK_SIZE    (configSTACK_DEPTH_TYPE)512  /* 增加 Stack 以容納 FPU 狀態 */
#define configTOTAL_HEAP_SIZE       ( ( size_t ) ( 256 * 1024 ) ) /* 為 AI 模型預留空間 */
#define configTICK_RATE_HZ          ((TickType_t)1000)

/* SMP 專屬設定 */
#define configNUMBER_OF_CORES       2
#define configUSE_PASSIVE_IDLE_HOOK  0
#define configTICK_CORE             0
#define configRUN_MULTIPLE_PRIORITIES 1

/* Cortex-M33 使用 3 bits 的優先權等級 (0-7) */
/* 數值越小代表優先權越高 */
#define configPRIO_BITS               3
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY      0x07
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 0x02

/* 實際暫存器使用的位移值 */
#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

/* 記憶體與排程管理 */
#define configMAX_PRIORITIES            32
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

/* 告訴 FreeRTOS 去哪裡讀取當前的 Core ID (CPUID 暫存器) */
#define configCORE_ID_REGISTER          ( SIO_BASE + SIO_CPUID_OFFSET )

/* 告訴 FreeRTOS 如何喚醒 Core 1 (使用 Pico SDK 的標準 API) */
extern long vPicoWakeSecondaryCore( void );
#define configWAKE_SECONDARY_CORES      vPicoWakeSecondaryCore

#endif /* FREERTOS_CONFIG_H */
