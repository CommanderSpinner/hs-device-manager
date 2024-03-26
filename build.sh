#!/bin/bash
gcc -o hsDeviceManager *c `pkg-config --cflags --libs gtk+-3.0`