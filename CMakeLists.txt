cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(pico2w_app C CXX ASM)
pico_sdk_init()

set(FREERTOS_KERNEL_PATH "/home/richard/Rasp_pico/FreeRTOS-Kernel")

# 1. 關鍵：手動定義 FreeRTOS 的源碼 (避免 Linker 找不到庫)
set(FREERTOS_SRC
    ${FREERTOS_KERNEL_PATH}/tasks.c
    ${FREERTOS_KERNEL_PATH}/list.c
    ${FREERTOS_KERNEL_PATH}/queue.c
    ${FREERTOS_KERNEL_PATH}/timers.c
    ${FREERTOS_KERNEL_PATH}/event_groups.c
    ${FREERTOS_KERNEL_PATH}/stream_buffer.c
    # 修正點：使用支援多核的 port.c
    ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/port.c
    ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c
)

# 2. 將 FreeRTOS 源碼加入執行檔
add_executable(pico2w_app 
    main.c 
    ${FREERTOS_SRC}
)

# 3. 設定 Include 路徑
target_include_directories(pico2w_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FREERTOS_KERNEL_PATH}/include
    # 修正點：必須指向支援 SMP 的 port 層
    ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/include
)

# 4. 連結其餘 SDK 庫 (移除原本報錯的 FreeRTOS-Kernel 字樣)
target_link_libraries(pico2w_app 
    pico_stdlib
    pico_multicore      # <--- 補上這行，解決 multicore_launch_core1 缺失問題 
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_enable_stdio_usb(pico2w_app 1)
pico_enable_stdio_uart(pico2w_app 0)
pico_add_extra_outputs(pico2w_app)
