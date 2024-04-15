#pragma once
typedef struct{
    int id;
    const char* name;
}Device;


void createDevice(Device *device, int id, const char* name);