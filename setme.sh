#!/bin/bash

TOOLCHAIN=arm-picolibc-eabi
test $TOOLCHAIN

TARGET=pico
test $TARGET

APP=usb_dev
test $APP

source ./.env

GDB=./toolchains/$TOOLCHAIN/bin/$TOOLCHAIN-gdb
test $GDB

APP_ELF=./build/$TARGET/apps/$APP.elf
test $APP_ELF

set -x
