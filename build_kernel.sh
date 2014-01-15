#!/bin/sh
echo "Starting build..."
ARCH=arm CROSS_COMPILE=/home/pepejson/android/toolchains/arm-linux-androideabi-4.7/bin/arm-linux-androideabi- make clean
ARCH=arm CROSS_COMPILE=/home/pepejson/android/toolchains/arm-linux-androideabi-4.7/bin/arm-linux-androideabi- make mars_haida_defconfig
ARCH=arm CROSS_COMPILE=/home/pepejson/android/toolchains/arm-linux-androideabi-4.7/bin/arm-linux-androideabi- make -j8
echo "Compile finished, building boot image"
cp /home/pepejson/android/Galaxy_Young/Kernel/arch/arm/boot/zImage /home/pepejson/android/Galaxy_Young/build_tools/zImage_Stock
cd /home/pepejson/android/Galaxy_Young/build_tools/
sh Make_Stock.sh $1
