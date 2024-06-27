#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

#ifdef __APPLE__
#include <IOKit/usb/IOUSBLib.h>
#include <IOKit/IOCFPlugIn.h>
#include <CoreFoundation/CoreFoundation.h>
#endif

// Plattformübergreifende Funktion zum Deaktivieren eines USB-Ports
void disable_usb_port(const char *port_identifier) {
#ifdef _WIN32
    // Windows spezifische Implementierung
    HDEVINFO device_info_set;
    SP_DEVINFO_DATA device_info_data;
    DWORD i;

    device_info_set = SetupDiGetClassDevs(NULL, "USB", NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (device_info_set == INVALID_HANDLE_VALUE) {
        printf("Error: SetupDiGetClassDevs failed\n");
        return;
    }

    device_info_data.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i = 0; SetupDiEnumDeviceInfo(device_info_set, i, &device_info_data); i++) {
        CHAR buffer[1024];
        DWORD size;
        if (SetupDiGetDeviceInstanceId(device_info_set, &device_info_data, buffer, sizeof(buffer), &size)) {
            if (strstr(buffer, port_identifier)) {
                SP_PROPCHANGE_PARAMS prop_change_params;
                prop_change_params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
                prop_change_params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
                prop_change_params.StateChange = DICS_DISABLE;
                prop_change_params.Scope = DICS_FLAG_GLOBAL;
                prop_change_params.HwProfile = 0;

                if (SetupDiSetClassInstallParams(device_info_set, &device_info_data, &prop_change_params.ClassInstallHeader, sizeof(prop_change_params)) &&
                    SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, device_info_set, &device_info_data)) {
                    printf("USB port %s disabled.\n", port_identifier);
                } else {
                    printf("Error: SetupDiCallClassInstaller failed\n");
                }
            }
        }
    }

    SetupDiDestroyDeviceInfoList(device_info_set);

#elif __linux__
    // Linux spezifische Implementierung
    char command[256];
    snprintf(command, sizeof(command), "echo '0' | sudo tee /sys/bus/usb/devices/%s/authorized", port_identifier);
    system(command);
    printf("USB port %s disabled.\n", port_identifier);

#elif __APPLE__
    // macOS spezifische Implementierung
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    io_iterator_t iterator;
    io_service_t usbDevice;
    kern_return_t kr;

    if (!matchingDict) {
        printf("Error: IOServiceMatching failed\n");
        return;
    }

    kr = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &iterator);
    if (kr != KERN_SUCCESS) {
        printf("Error: IOServiceGetMatchingServices failed\n");
        return;
    }

    while ((usbDevice = IOIteratorNext(iterator))) {
        CFStringRef productID = IORegistryEntryCreateCFProperty(usbDevice, CFSTR(kUSBProductString), kCFAllocatorDefault, 0);
        if (productID) {
            const char *cStr = CFStringGetCStringPtr(productID, kCFStringEncodingUTF8);
            if (cStr && strstr(cStr, port_identifier)) {
                IOObjectRelease(usbDevice);
                printf("USB port %s disabled.\n", port_identifier);
                break;
            }
            CFRelease(productID);
        }
        IOObjectRelease(usbDevice);
    }

    IOObjectRelease(iterator);

#else
    // Fallback für andere Plattformen
    printf("Error: Platform not supported\n");
#endif
}

// Plattformübergreifende Funktion zum Aktivieren oder Deaktivieren eines USB-Ports
void toggle_usb_port(const char *port_identifier, int enable) {
#ifdef _WIN32
    // Windows spezifische Implementierung
    HDEVINFO device_info_set;
    SP_DEVINFO_DATA device_info_data;
    DWORD i;

    device_info_set = SetupDiGetClassDevs(NULL, "USB", NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (device_info_set == INVALID_HANDLE_VALUE) {
        printf("Error: SetupDiGetClassDevs failed\n");
        return;
    }

    device_info_data.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i = 0; SetupDiEnumDeviceInfo(device_info_set, i, &device_info_data); i++) {
        CHAR buffer[1024];
        DWORD size;
        if (SetupDiGetDeviceInstanceId(device_info_set, &device_info_data, buffer, sizeof(buffer), &size)) {
            if (strstr(buffer, port_identifier)) {
                SP_PROPCHANGE_PARAMS prop_change_params;
                prop_change_params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
                prop_change_params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
                prop_change_params.StateChange = enable ? DICS_ENABLE : DICS_DISABLE; // Toggle between enable and disable
                prop_change_params.Scope = DICS_FLAG_GLOBAL;
                prop_change_params.HwProfile = 0;

                if (SetupDiSetClassInstallParams(device_info_set, &device_info_data, &prop_change_params.ClassInstallHeader, sizeof(prop_change_params)) &&
                    SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, device_info_set, &device_info_data)) {
                    if (enable)
                        printf("USB port %s enabled.\n", port_identifier);
                    else
                        printf("USB port %s disabled.\n", port_identifier);
                } else {
                    printf("Error: SetupDiCallClassInstaller failed\n");
                }
            }
        }
    }

    SetupDiDestroyDeviceInfoList(device_info_set);

#elif __linux__
    // Linux spezifische Implementierung
    char command[256];
    snprintf(command, sizeof(command), "echo '%d' | sudo tee /sys/bus/usb/devices/%s/authorized", enable, port_identifier);
    system(command);
    if (enable)
        printf("USB port %s enabled.\n", port_identifier);
    else
        printf("USB port %s disabled.\n", port_identifier);

#elif __APPLE__
    // macOS spezifische Implementierung
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    io_iterator_t iterator;
    io_service_t usbDevice;
    kern_return_t kr;

    if (!matchingDict) {
        printf("Error: IOServiceMatching failed\n");
        return;
    }

    kr = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &iterator);
    if (kr != KERN_SUCCESS) {
        printf("Error: IOServiceGetMatchingServices failed\n");
        return;
    }

    while ((usbDevice = IOIteratorNext(iterator))) {
        CFStringRef productID = IORegistryEntryCreateCFProperty(usbDevice, CFSTR(kUSBProductString), kCFAllocatorDefault, 0);
        if (productID) {
            const char *cStr = CFStringGetCStringPtr(productID, kCFStringEncodingUTF8);
            if (cStr && strstr(cStr, port_identifier)) {
                IOObjectRelease(usbDevice);
                printf("USB port %s %s.\n", port_identifier, enable ? "enabled" : "disabled");
                break;
            }
            CFRelease(productID);
        }
        IOObjectRelease(usbDevice);
    }

    IOObjectRelease(iterator);

#else
    // Fallback für andere Plattformen
    printf("Error: Platform not supported\n");
#endif
}
