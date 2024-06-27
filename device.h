#pragma once
typedef struct{
    int id;
    const char* name;
    bool isActive;
}Device;

int getDevicesCount();

Device* getDeviceNames();

//void createDevice(Device *device, int id, const char* name);