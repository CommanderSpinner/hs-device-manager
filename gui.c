#include <gtk/gtk.h>
#include "gui.h"

// Struktur zur Darstellung der Informationen eines Geräts
typedef struct {
    char *name;
    char *description;
} DeviceInfo;

// Callback-Funktion, die aufgerufen wird, wenn das Fenster geschlossen wird
static void on_window_closed(GtkWidget *widget, gpointer data) {
    gtk_main_quit(); // Beendet die GTK-Hauptschleife
}

// Funktion zum Erstellen eines Labels für ein Gerät
static GtkWidget* create_device_label(DeviceInfo *device_info) {
    GtkWidget *label = gtk_label_new(NULL);
    char *markup = g_strdup_printf("<b>%s</b>\n<i>%s</i>", device_info->name, device_info->description);
    gtk_label_set_markup(GTK_LABEL(label), markup);
    g_free(markup);
    return label;
}

// Funktion zum Erstellen und Anzeigen der GUI
void initGui(int argc, char** argv, DeviceInfo *devices, int num_devices){
    // Initialisiere GTK
    gtk_init(&argc, &argv);

    // Erstelle ein Fenster
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Geräteübersicht");
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);

    // Erstelle eine Box für die Geräte
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Füge Labels für jedes Gerät hinzu
    for (int i = 0; i < num_devices; i++) {
        GtkWidget *label = create_device_label(&devices[i]);
        gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    }

    // Zeige das Fenster und alle darin enthaltenen Widgets an
    gtk_widget_show_all(window);

    // Starte die GTK-Hauptschleife
    gtk_main();
}
