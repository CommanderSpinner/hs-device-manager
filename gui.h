#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "deviceManager.h"

/*
// Struktur zur Darstellung der Informationen eines Geräts
typedef struct {
    char *name;
    char *description;
} DeviceInfo;

// Struktur für die Geräteliste
typedef struct {
    DeviceInfo *devices;
    int num_devices;
} DeviceList;
*/

// Funktion zum Initialisieren der GUI
void initGui(int argc, char** argv, DeviceList *devices);
void updateDeviceList(DeviceList *devices);

#endif /* GUI_H */
