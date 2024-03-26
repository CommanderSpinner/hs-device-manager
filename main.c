#include <stdio.h>
#include <gtk/gtk.h>
#include <libusb-1.0/libusb.h>
#include "gui.h"
#include "deviceManager.h"

// Deklaration der Funktion updateDeviceList
void updateDeviceList(DeviceList *devices);

int main(int argc, char** argv) {
    printf("\nHS device manager");

    // Erstelle eine Geräteliste
    DeviceList *di = initDeviceList();
    if (di == NULL) {
        fprintf(stderr, "Fehler: Geräteliste konnte nicht initialisiert werden.\n");
        return 1;
    }

    // Füge einige Geräte hinzu
    addDevice(di, "Gerät 1", "Dies ist Gerät 1");
    addDevice(di, "Gerät 2", "Dies ist Gerät 2");

    // Initialisiere die GUI
    initGui(argc, argv, di);

    // Aktualisiere die Geräteliste und die GUI
    updateDeviceList(di);

    // Gib den Speicher frei
    freeDeviceList(di);

    return 0;
}
