// gui.h

#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

// Function to create the GUI window
GtkWidget* create_window();

extern GtkWidget *window;
// Function to dynamically add buttons
void add_button(GtkWidget* window, const char* label);

#endif // GUI_H
