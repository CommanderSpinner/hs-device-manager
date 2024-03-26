#ifndef GUI_H
#define GUI_H

// Struktur zur Darstellung der Informationen eines Geräts
typedef struct {
    char *name;
    char *description;
} DeviceInfo;

// Funktion zum Initialisieren und Anzeigen der GUI
void initGui(int argc, char** argv, DeviceInfo *devices, int num_devices);

#endif /* GUI_H */
