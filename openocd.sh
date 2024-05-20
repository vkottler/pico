#!/bin/bash

source ./setme.sh

# need to figure out why this needs sudo
sudo openocd \
	-f interface/cmsis-dap.cfg \
	-f target/rp2040.cfg \
	-c "adapter speed 5000" \
	-c "program $APP_ELF verify reset exit"
