#Build command:

cd ~/Rasp_pico/MyProject
rm -rf build
mkdir build
cd build

cmake -DPICO_PLATFORM=rp2350-arm-s -DPICO_BOARD=pico2_w ..

make -j$(nproc)


#============FreeRTOS-Kernel===========================

Source: https://github.com/raspberrypi/pico-sdk

richard@richard-virtual-machine:~/Rasp_pico/FreeRTOS-Kernel$ git branch -a
* main
  remotes/origin/HEAD -> origin/main
  remotes/origin/main
richard@richard-virtual-machine:~/Rasp_pico/FreeRTOS-Kernel$ git describe --tags
fatal: No names found, cannot describe anything.
richard@richard-virtual-machine:~/Rasp_pico/FreeRTOS-Kernel$ git log
commit 4f7299d6ea746b27a9dd19e87af568e34bd65b15 (HEAD -> main, origin/main, origin/HEAD)
Author: graham sanderson <graham.sanderson@raspeberryi.com>
Date:   Wed Jul 31 16:42:14 2024 -0500

    Add two RP2350 ports:

    RP2350_ARM_NTZ - Arm Secure-only Non-TrustZone port for RP2350
    RP2350_RISC-V - RISC-V port for RP2350



#============pico-sdk===========================

richard@richard-virtual-machine:~/Rasp_pico/pico-sdk$ git branch -a
* (no branch)
  remotes/origin/HEAD -> origin/master
  remotes/origin/bazel-missing-configs
  remotes/origin/develop
  remotes/origin/develop-hwtests
  remotes/origin/fix-exec2-removal
  remotes/origin/fix_irq_comments
  remotes/origin/hardware-header-updates
  remotes/origin/iar/develop
  remotes/origin/lurch-patch-3
  remotes/origin/lurch-patch-4
  remotes/origin/master
  remotes/origin/ns-alpha
  remotes/origin/pico-psram
  remotes/origin/pioasm-cflags
  remotes/origin/rom_version
  remotes/origin/spinlocks
  remotes/origin/tls-support
richard@richard-virtual-machine:~/Rasp_pico/pico-sdk$ git describe --tags
2.1.0
richard@richard-virtual-machine:~/Rasp_pico/pico-sdk$ git describe --tags
2.1.0
richard@richard-virtual-machine:~/Rasp_pico/pico-sdk$ git log
commit 95ea6acad131124694cda1c162c52cd30e0aece0 (HEAD, tag: 2.1.0)
Author: graham sanderson <graham.sanderson@raspberrypi.com>
Date:   Sun Nov 24 20:36:31 2024 -0600

    SDK 2.1.0 release


