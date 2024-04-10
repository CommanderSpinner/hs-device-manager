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

void programm(Devices d){
    
    gtk_widget_show_all(window);

    for(int i)

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


