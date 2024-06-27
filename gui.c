#include <gtk/gtk.h>
#include "gui.h"
#include "device.h"

int deviceCount = 0;
GtkWidget *window = NULL;
GtkWidget *box = NULL;

static void on_button_clicked(GtkWidget *button, Device* d) {
    g_print("Button clicked for %s %d!\n", d->name, d->id);
    
}

void initGui(int argc, char **argv) {
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Device Buttons");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_size_request(window, 600, 800);
    gtk_window_move(window, 100, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 5 is spacing between children
    gtk_container_add(GTK_CONTAINER(window), box);
}

void addButton(Device *device) {
    GtkWidget *button;
    char label[20];
    sprintf(label, "%d: %s", device->id, device->name);
    button = gtk_button_new_with_label(label);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), device);
    gtk_container_add(GTK_CONTAINER(box), button); // Add button to the box container
}

void quitGui() {
    gtk_widget_destroy(window);
}

int main(int argc, char **argv) {
    initGui(argc, argv);

    // Simulated device initialization
    deviceCount = getDevicesCount();

    g_print("device count: %i", deviceCount);

    Device devices[deviceCount];
    for (int i = 0; i < deviceCount; i++) {
        devices[i].id = i + 1;
        devices[i].name = "test";
        addButton(&devices[i]);
    }

    gtk_widget_show_all(window);

    gtk_main();

    quitGui();

    return 0;
}


/*
void initGui(int argc, char **argv) {
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Device Buttons");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_size_request(window, 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Beende die GTK-Hauptschleife beim Schließen des Fensters
}


void addButton(Device *devices) {
        GtkWidget *button;
        char label[20];
        //printf(label, "Device %d", devices->id);
        button = gtk_button_new_with_label(label);
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), &devices);
        gtk_container_add(GTK_CONTAINER(window), button);
}

void addButton(Device *device) {
    GtkWidget *button;
    char label[20];
    sprintf(label, "Device %d", device->id);
    button = gtk_button_new_with_label(label);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), device); // Pass device instead of &devices
    gtk_container_add(GTK_CONTAINER(window), button);
}
*/

/*
#include <gtk/gtk.h>
#include "gui.h"
#include "device.h"

static void on_button_clicked(GtkWidget* button, Device d) {
    g_print("Button clicked!\n");
}

void initGui(int argc, char** argv){
    gtk_init(&argc, &argv);
    gtk_window_set_resizable(window, FALSE);
    gtk_window_resize(GTK_WINDOW(window), 600, 400);
}

void programm(Device d){
    
    gtk_widget_show_all(window);

    for(int i = 0; i < deviceCount; i++){
        
    }

    GtkWidget* button; 
    button = gtk_button_new_with_label("Click me");



    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_main();
}

void quitGui(){


}


int main(int argc, char** argv) {

    initGui(&argc, &argv);

    Device d;
    programm(d);

    quitGui();

    return 0;
}
*/