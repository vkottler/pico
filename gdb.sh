#!/bin/bash

source ./setme.sh

ninja
$GDB $APP_ELF
