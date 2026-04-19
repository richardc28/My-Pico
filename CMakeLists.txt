cmake_minimum_required(VERSION 3.13)
# 設定硬體為 RP2350 (這是 Pico 2 W 的心臟)
set(PICO_PLATFORM rp2350-arm-s) # 明確指定 ARM 安全模式
set(PICO_BOARD pico2_w)

include(pico_sdk_import.cmake)
project(pico2w_app C CXX ASM)
pico_sdk_init()


set(FREERTOS_KERNEL_PATH "/home/richard/Rasp_pico/FreeRTOS-Kernel")

# 1. 修正：指向正確的 Cortex-M33 SMP Port
# 注意：這裡我們使用你剛才 ls 確認過的 ARM_CM33_NTZ 路徑
set(FREERTOS_PORT_DIR ${FREERTOS_KERNEL_PATH}/portable/GCC/ARM_CM33_NTZ/non_secure)

set(FREERTOS_SRC
    ${FREERTOS_KERNEL_PATH}/tasks.c
    ${FREERTOS_KERNEL_PATH}/list.c
    ${FREERTOS_KERNEL_PATH}/queue.c
    ${FREERTOS_KERNEL_PATH}/timers.c
    ${FREERTOS_KERNEL_PATH}/event_groups.c
    ${FREERTOS_KERNEL_PATH}/stream_buffer.c
    ${FREERTOS_PORT_DIR}/port.c          # <--- 修正：使用 M33 原生 port.c
    ${FREERTOS_PORT_DIR}/portasm.c       # <--- 修正：M33 需要彙編支援
    ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c
)

add_compile_options(
    -mcpu=cortex-m33
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
)

add_link_options(
    -mcpu=cortex-m33
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
)

# 2. 將源碼加入執行檔
add_executable(pico2w_app
    main.c
    ${FREERTOS_SRC}
)

set_target_properties(pico2w_app PROPERTIES
    COMPILE_FLAGS "-mfloat-abi=hard -mfpu=fpv5-sp-d16"
    LINK_FLAGS "-mfloat-abi=hard -mfpu=fpv5-sp-d16"
)

# 3. 修正 Include 路徑
target_include_directories(pico2w_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FREERTOS_KERNEL_PATH}/include
    ${FREERTOS_PORT_DIR}                 # <--- 修正：指向 M33 port 標頭檔
)

# 4. 連結其餘 SDK 庫
target_link_libraries(pico2w_app
    pico_stdlib
    pico_multicore      
    pico_cyw43_arch_lwip_threadsafe_background
)

# 在 target_link_libraries 之後加入這段
target_compile_options(pico2w_app PUBLIC
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
)

# 關鍵修正：讓 Linker 也帶上正確的 FPU 參數
target_link_options(pico2w_app PUBLIC
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
)

# 5. 編譯優化：確保開啟 FPU (這對接下來的 Edge Impulse AI 極度重要)
target_compile_options(pico2w_app PRIVATE
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
)

pico_enable_stdio_usb(pico2w_app 1)
pico_enable_stdio_uart(pico2w_app 0)
pico_add_extra_outputs(pico2w_app)

