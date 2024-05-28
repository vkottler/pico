#!/bin/bash

source ./setme.sh

OPENOCD_ARGS=()

run_openocd() {
	openocd "${OPENOCD_ARGS[@]}"
}

add_rp2040_args() {
	OPENOCD_ARGS+=(-f interface/cmsis-dap.cfg)
	OPENOCD_ARGS+=(-f target/rp2040.cfg)
	OPENOCD_ARGS+=(-c "adapter speed 5000")
}

openocd_program() {
	OPENOCD_ARGS+=(-c "program $APP_ELF verify reset exit")
}

add_rp2040_args

# For flashing.
# openocd_program

run_openocd
