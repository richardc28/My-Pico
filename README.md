\#Build command:

cd \~/Rasp\_pico/MyProject
rm -rf build
mkdir build
cd build

cmake -DPICO\_PLATFORM=rp2350-arm-s -DPICO\_BOARD=pico2\_w ..

make -j$(nproc)



\#Debug Pbobe:

\#Build \& Configure:

./bootstrap

./configure --disable-werror



\#Run:

sudo src/openocd -s tcl -f interface/cmsis-dap.cfg -f target/rp2350.cfg -c "adapter speed 5000"



\#============FreeRTOS-Kernel===========================

Source: https://github.com/raspberrypi/pico-sdk

richard@richard-virtual-machine:\~/Rasp\_pico/FreeRTOS-Kernel$ git branch -a

* main
remotes/origin/HEAD -> origin/main
remotes/origin/main
richard@richard-virtual-machine:\~/Rasp\_pico/FreeRTOS-Kernel$ git describe --tags
fatal: No names found, cannot describe anything.
richard@richard-virtual-machine:\~/Rasp\_pico/FreeRTOS-Kernel$ git log
commit 4f7299d6ea746b27a9dd19e87af568e34bd65b15 (HEAD -> main, origin/main, origin/HEAD)
Author: graham sanderson [graham.sanderson@raspeberryi.com](mailto:graham.sanderson@raspeberryi.com)
Date:   Wed Jul 31 16:42:14 2024 -0500

  Add two RP2350 ports:

  RP2350\_ARM\_NTZ - Arm Secure-only Non-TrustZone port for RP2350
RP2350\_RISC-V - RISC-V port for RP2350



  \#============pico-sdk===========================

  richard@richard-virtual-machine:\~/Rasp\_pico/pico-sdk$ git branch -a

* (no branch)
remotes/origin/HEAD -> origin/master
remotes/origin/bazel-missing-configs
remotes/origin/develop
remotes/origin/develop-hwtests
remotes/origin/fix-exec2-removal
remotes/origin/fix\_irq\_comments
remotes/origin/hardware-header-updates
remotes/origin/iar/develop
remotes/origin/lurch-patch-3
remotes/origin/lurch-patch-4
remotes/origin/master
remotes/origin/ns-alpha
remotes/origin/pico-psram
remotes/origin/pioasm-cflags
remotes/origin/rom\_version
remotes/origin/spinlocks
remotes/origin/tls-support
richard@richard-virtual-machine:\~/Rasp\_pico/pico-sdk$ git describe --tags
2.1.0
richard@richard-virtual-machine:\~/Rasp\_pico/pico-sdk$ git describe --tags
2.1.0
richard@richard-virtual-machine:\~/Rasp\_pico/pico-sdk$ git log
commit 95ea6acad131124694cda1c162c52cd30e0aece0 (HEAD, tag: 2.1.0)
Author: graham sanderson [graham.sanderson@raspberrypi.com](mailto:graham.sanderson@raspberrypi.com)
Date:   Sun Nov 24 20:36:31 2024 -0600

  SDK 2.1.0 release

