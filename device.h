#include <stdbool.h>
#include <stdlib.h>

#pragma once
typedef struct{
    int id;
    const char* name;
    bool isActive;
    const char* port_identifier;
}Device;


void deactivadeDevice(Device *d);

int getDevicesCount();

const char* getDeviceName();

//void createDevice(Device *device, int id, const char* name);