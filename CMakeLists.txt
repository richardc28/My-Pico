cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico2w_app C CXX ASM)

# 這會幫你設定好 RP2350 的編譯鏈與硬體定義
pico_sdk_init()

# 1. 設定新路徑 (Raspberry Pi 官方版)
set(FREERTOS_KERNEL_PATH "/home/richard/Rasp_pico/FreeRTOS-Kernel")

# 2. 關鍵：指向 RP2350 專用的 Port 路徑
set(FREERTOS_PORT_DIR ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2350_ARM_NTZ/non_secure)

set(FREERTOS_SRC
    ${FREERTOS_KERNEL_PATH}/tasks.c
    ${FREERTOS_KERNEL_PATH}/list.c
    ${FREERTOS_KERNEL_PATH}/queue.c
    ${FREERTOS_KERNEL_PATH}/timers.c
    ${FREERTOS_KERNEL_PATH}/event_groups.c
    ${FREERTOS_KERNEL_PATH}/stream_buffer.c
    ${FREERTOS_PORT_DIR}/port.c        # 使用 Pi 官方專為 RP2350 寫的 Port
    ${FREERTOS_PORT_DIR}/portasm.c
    ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c
)

# 3. 定義執行檔
add_executable(pico2w_app 
    main.c 
    ${FREERTOS_SRC}
)

# 4. Include 路徑
target_include_directories(pico2w_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FREERTOS_KERNEL_PATH}/include
    ${FREERTOS_PORT_DIR}
)

target_link_libraries(pico2w_app 
    pico_stdlib
    pico_multicore
    hardware_exception   # <--- 解決 "hardware/exception.h" 缺失
    hardware_timer       # <--- Port 內部通常需要精確計時
    hardware_sync        # <--- 處理 Spinlock 和中斷鎖
)

# 5. 啟用 USB 輸出並產生 UF2
pico_enable_stdio_usb(pico2w_app 1)
pico_add_extra_outputs(pico2w_app)
