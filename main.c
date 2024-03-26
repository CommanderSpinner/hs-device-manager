#include <stdio.h>
#include <gtk/gtk.h>
#include <libusb-1.0/libusb.h>
#include "gui.h"
#include "deviceManager.h"

int num_Devices;
DeviceInfo* di;

int main(int argc, char** argv){
    printf("\nHS device manager");

    di->name = "test";
    di->description = "TEST";

    initGui(argc, argv, di, num_Devices);

    return 0;
}