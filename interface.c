#include <gtk/gtk.h>
#include "operations.h"

GtkWidget *buttons_numbers[10];
for (int i = 0; i < 10; i++) {
    char label[2];
    snprintf(label, sizeof(label), "%d", i); 
    buttons_numbers[i] = gtk_button_new_with_label(label);
};
GtkWidget *buttonEquals = gtk_button_new_with_label("=");
GtkWidget *buttonAdd = gtk_button_new_with_label("+");
GtkWidget *buttonSub = gtk_button_new_with_label("-");
GtkWidget *buttonDiv = gtk_button_new_with_label("/");
GtkWidget *buttonMul = gtk_button_new_with_label("*");
GtkWidget *buttonClean = gtk_button_new_with_label("C");

int row = 1;
int col = 0;

for(int i = 0; i =< 9; i++){
    gtk_grid_attach(GTK_GRID(grid), buttons_numbers[i], col, row, 1, 1);
    col++;
    if(col == 4){
        col = 0;
        row++;
    }
};
gtk_grid_attach(GTK_GRID(grid), digit_buttons[0], 1, row, 1, 1);
gtk_grid_attach(GTK_GRID(grid), buttonEquals, 0, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), buttonAdd, 1, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), buttonSub, 2, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), buttonDiv, 3, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), buttonMul, 4, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), buttonClean, 5, 3, 1, 1);

for(int i = 0; i =< 10; i++){
    g_signal_connect(buttons_numbers[i], "clicked", G_CALLBACK(on_buttons_numbers), entry);
}

void on_buttons_numbers(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    const gchar *current = gtk_entry_get_text(entry);
    gchar *new_text = g_strconcat(current, label, NULL);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);

}

g_signal_connect(buttonAdd, "clicked", G_CALLBACK(on_buttons_operations), entry);
g_signal_connect(buttonSub, "clicked", G_CALLBACK(on_buttons_operations), entry);
g_signal_connect(buttonDiv, "clicked", G_CALLBACK(on_buttons_operations), entry);
g_signal_connect(buttonMul, "clicked", G_CALLBACK(on_buttons_operations), entry);