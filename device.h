#pragma once
typedef struct{
    int id;
    const char* name;
}Device;

Device* getDeviceNames();

//void createDevice(Device *device, int id, const char* name);