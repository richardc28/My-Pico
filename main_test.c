#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    // 初始化 stdio
    stdio_init_all();

    // 給 Windows 5 秒鐘反應，這期間什麼都不要做
    for(int i = 5; i > 0; i--) {
        sleep_ms(1000);
    }

    while (1) {
        printf("Pico 2 WH is Alive on USB!\r\n");
        sleep_ms(1000);
    }
}