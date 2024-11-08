#!/bin/bash

TOOLCHAIN=arm-picolibc-eabi
test $TOOLCHAIN

TARGET=pico
test $TARGET

APP=test_app
test $APP

source ./.env

# Not working.
# GDB=./toolchains/$TOOLCHAIN/bin/$TOOLCHAIN-gdb
GDB=gdb-multiarch
test $GDB

APP_ELF=./build/$TARGET/apps/$APP.elf
test $APP_ELF

set -x
