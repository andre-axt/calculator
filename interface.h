#ifndef INTERFACE_H
#define INTERFACE_H
#include <gtk/gtk.h>

void activate(GtkApplication *app, gpointer user_data);
void on_buttons_numbers(GtkWidget *widget, gpointer data);
void on_buttons_operations(GtkWidget *widget, gpointer data);
void on_button_equals(GtkWidget *widget, gpointer data);
void on_button_clear(GtkWidget *widget, gpointer data);

extern GtkWidget *entry;

#endif