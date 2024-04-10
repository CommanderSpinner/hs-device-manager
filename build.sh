#!bin/bash
gcc `pkg-config --cflags gtk+-3.0` -o hsDeviceManager main.c gui.c device.c `pkg-config --libs gtk+-3.0`
