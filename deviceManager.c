#include "deviceManager.h"
// Funktion zum Initialisieren der Geräteliste
DeviceList* initDeviceList() {
    DeviceList *list = malloc(sizeof(DeviceList));
    if (list == NULL) {
        fprintf(stderr, "Fehler: Speicher konnte nicht zugewiesen werden.\n");
        return NULL;
    }
    list->devices = NULL;
    list->num_devices = 0;
    return list;
}

// Funktion zum Hinzufügen eines Geräts zur Geräteliste
void addDevice(DeviceList *list, const char *name, const char *description) {
    // Code zum Hinzufügen eines Geräts zur Liste
}

// Funktion zum Freigeben des Speichers der Geräteliste
void freeDeviceList(DeviceList *list) {
    // Code zum Freigeben des Speichers der Geräteliste
}