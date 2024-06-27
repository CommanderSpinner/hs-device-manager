#pragma once
typedef struct{
    int id;
    const char* name;
    bool isActive;
    void deactiveDevice();
}Device;

int getDevicesCount();

Device* getDeviceName();

//void createDevice(Device *device, int id, const char* name);