#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <devpkey.h>

// Funktion zum Abfragen des Gerätestatus unter Windows
int getUSBDeviceStateWindows(const char* deviceInstanceId) {
    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD i;
    BOOL status;

    deviceInfoSet = SetupDiGetClassDevs(NULL, "USB", NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        return -1;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        char buffer[512];
        DWORD bufferSize = 0;

        if (SetupDiGetDeviceInstanceId(deviceInfoSet, &deviceInfoData, buffer, sizeof(buffer), &bufferSize)) {
            if (strcmp(buffer, deviceInstanceId) == 0) {
                DWORD state;
                if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_CONFIGFLAGS, NULL, (PBYTE)&state, sizeof(state), NULL)) {
                    SetupDiDestroyDeviceInfoList(deviceInfoSet);
                    return (state & CONFIGFLAG_DISABLED) ? 0 : 1;
                }
            }
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return -1;
}

int setUSBDeviceStateWindows(int enable, const char* deviceInstanceId) {
    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD i;
    BOOL status;

    deviceInfoSet = SetupDiGetClassDevs(NULL, "USB", NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        return -1;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        char buffer[512];
        DWORD bufferSize = 0;

        if (SetupDiGetDeviceInstanceId(deviceInfoSet, &deviceInfoData, buffer, sizeof(buffer), &bufferSize)) {
            if (strcmp(buffer, deviceInstanceId) == 0) {
                status = SetupDiSetClassInstallParams(deviceInfoSet, &deviceInfoData, NULL, 0);
                if (enable) {
                    status = SetupDiEnableDevice(deviceInfoSet, &deviceInfoData);
                } else {
                    status = SetupDiDisableDevice(deviceInfoSet, &deviceInfoData);
                }

                SetupDiDestroyDeviceInfoList(deviceInfoSet);
                return status ? 0 : -1;
            }
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return -1;
}

#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// Funktion zum Abfragen des Gerätestatus unter Linux
int getUSBDeviceStateLinux(const char* portPath) {
    int fd;
    char path[256];
    char state;
    snprintf(path, sizeof(path), "%s/authorized", portPath);

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        return -1;
    }

    if (read(fd, &state, 1) == -1) {
        close(fd);
        return -1;
    }

    close(fd);
    return (state == '1') ? 1 : 0;
}

int setUSBDeviceStateLinux(int enable, const char* portPath) {
    int fd;
    char path[256];
    char state = enable ? '1' : '0';
    snprintf(path, sizeof(path), "%s/authorized", portPath);

    fd = open(path, O_WRONLY);
    if (fd == -1) {
        return -1;
    }

    if (write(fd, &state, 1) == -1) {
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}
#endif

int toggleUSBDeviceState(const char* identifier) {
#ifdef _WIN32
    int currentState = getUSBDeviceStateWindows(identifier);
    if (currentState == -1) {
        return -1;
    }
    return setUSBDeviceStateWindows(!currentState, identifier);
#else
    int currentState = getUSBDeviceStateLinux(identifier);
    if (currentState == -1) {
        return -1;
    }
    return setUSBDeviceStateLinux(!currentState, identifier);
#endif
}