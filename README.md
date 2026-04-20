#Build command:

cd ~/Rasp_pico/MyProject
rm -rf build
mkdir build
cd build

cmake -DPICO_PLATFORM=rp2350-arm-s \
      -DCMAKE_C_FLAGS="-mfloat-abi=hard -mfpu=fpv5-sp-d16" \
      -DCMAKE_CXX_FLAGS="-mfloat-abi=hard -mfpu=fpv5-sp-d16" \
      ..

make -j$(nproc)


#============FreeRTOS-Kernel===========================

richard@richard-virtual-machine:~/Rasp_pico/FreeRTOS-Kernel$ git branch -a
* main
  smp
  remotes/origin/HEAD -> origin/main
  remotes/origin/ci-test
  remotes/origin/main
  remotes/origin/smp
richard@richard-virtual-machine:~/Rasp_pico/FreeRTOS-Kernel$ git describe --tags
V10.4.3-769-g7c0c890c6


#============pico-sdk===========================

richard@richard-virtual-machine:~/Rasp_pico/pico-sdk$ git branch -a

* (no branch)

  remotes/origin/HEAD -> origin/master

  remotes/origin/bazel-missing-configs

  remotes/origin/develop

  remotes/origin/float-benchmark

  remotes/origin/float_test_fixes

  remotes/origin/host_build_fixes

  remotes/origin/iar/develop

  remotes/origin/lurch-patch-1

  remotes/origin/lurch-patch-2

  remotes/origin/lurch-patch-3

  remotes/origin/lurch-patch-4

  remotes/origin/master

  remotes/origin/ns-alpha

  remotes/origin/pioasm-cflags

  remotes/origin/rom_version

  remotes/origin/spinlocks

richard@richard-virtual-machine:~/Rasp_pico/pico-sdk$ git describe --tags

2.1.0
