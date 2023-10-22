#!/bin/bash

TOOLCHAIN=arm-picolibc-eabi

TARGET=pico
APP=test_file

source ./.env
set -x

ninja
./toolchains/$TOOLCHAIN/bin/$TOOLCHAIN-gdb ./build/$TARGET/apps/$APP.elf
