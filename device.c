#include "device.h"
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>

int getDevicesCount(){
    libusb_device **devs;
    libusb_context *ctx = NULL;
    int r;
    ssize_t cnt = 0;

    r = libusb_init(&ctx);
    if (r < 0) {
        fprintf(stderr, "Error initializing libusb: %s\n", libusb_strerror(r));
        return -1;
    }

    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        fprintf(stderr, "Error getting device list: %s\n", libusb_strerror((int)cnt));
        libusb_exit(ctx);
        return -1;
    }

    // Free the device list
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);

    return (int)cnt;
}

void deactivadeDevice(){
    
}

Device* getDeviceName(){
    Device* devices;


    return devices;
}
/*
void createDevice(Device *device, int id, const char* name){
    id = 0;
    device->name = name;
}

*/