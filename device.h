#pragma once
typedef struct{
    int id;
    const char* name;
    bool isActive;
    void deactivadeDevice();
    const char* port_identifier;
}Device;

int getDevicesCount();

Device* getDeviceName();

//void createDevice(Device *device, int id, const char* name);