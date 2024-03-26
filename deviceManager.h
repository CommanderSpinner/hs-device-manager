#pragma once
#include <gtk-3.0/gtk/gtk.h>
#include <libusb-1.0/libusb.h>
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

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

// Funktion zum Initialisieren der Geräteliste
DeviceList* initDeviceList();

// Funktion zum Hinzufügen eines Geräts zur Geräteliste
void addDevice(DeviceList *list, const char *name, const char *description);

// Funktion zum Freigeben des Speichers der Geräteliste
void freeDeviceList(DeviceList *list);

#endif /* DEVICEMANAGER_H */
