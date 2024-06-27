#!bin/bash
#clang `pkg-config --cflags gtk+-3.0` -o hsDeviceManager main.c gui.c device.c `pkg-config --libs gtk+-3.0`
clang $(pkg-config --cflags gtk+-3.0) $(pkg-config --cflags libusb-1.0) -o hsDeviceManager main.c gui.c device.c $(pkg-config --libs gtk+-3.0) $(pkg-config --libs libusb-1.0) && ./hsDeviceManager
