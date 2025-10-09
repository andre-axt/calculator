#ifndef INTERFACE_H
#define INTERFACE_H
#include <gtk/gtk.h>

void activate(GtkApplication *app, gpointer user_data);
void on_button_clicked(GtkWidget *widget, gpointer data);
void on_button_equals(GtkWidget *widget, gpointer data);
void on_clear_clicked(GtkWidget *widget, gpointer data);
void create_calculator_window(void);

extern GtkWidget *entry;

#endif