#include <gtk/gtk.h>
#include "operations.h"
#include "string.h"
#include <stdlib.h>

void on_buttons_numbers(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    const gchar *current = gtk_entry_get_text(entry);
    gchar *new_text = g_strconcat(current, label, NULL);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}

void on_buttons_operations(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    const gchar *current = gtk_entry_get_text(entry);
    int current_len = strlen(current);
    if(current_len > 0 && current[current_len - 1] != '+' && current[current_len - 1] != '-' && current[current_len - 1] != '*' && current[current_len - 1] != '/'){
          gchar  *new_text = g_strconcat(current, label, NULL);
          gtk_entry_set_text(entry, new_text);
          g_free(new_text);
    }
}

void on_button_clear(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    gtk_entry_set_text(entry, "");
}

void on_button_equals(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *current = gtk_entry_get_text(entry);
    char op[4] = { '+', '-', '/', '*'};
    int i;
    
    for(i = 0; i < 4; i++){
        char x = op[i];
        char *pos = strchr(current, x);
        if(pos){
            int op_index = pos - current;
            char left[op_index + 1];
            strncpy(left, current, op_index);
            left[op_index] = '\0';
            const char *right = pos + 1;
            double a = atof(left);
            double b = atof(right);
            double result;
            switch (x)
            {
            case '+':
                result = add(a, b);
                break;
            
            case '-':
                result = sub(a, b);
                break;
            
            case '/':
                result = divide(a, b);
                break;
            
            case '*':
                result = mul(a, b);
                break;
            
            default:
                break;
            }
            char result_str[32];
            sprintf(result_str, "%.2f", result);
            gtk_entry_set_text(entry, result_str);
            break;
        }
    }
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *buttonAdd, *buttonSub, *buttonMul, *buttonDiv, *buttonClear, *buttonEquals;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 300);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    const char *labels[] = {
        "7", "8", "9", "+",
        "4", "5", "6", "-",
        "1", "2", "3", "*",
        "C", "0", "=", "/"
    };

    for (int i = 0; i < 16; i++) {
        GtkWidget *button = gtk_button_new_with_label(labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, 1 + i / 4, 1, 1);

        if (g_strcmp0(labels[i], "+") == 0) {
            buttonAdd = button;
        } else if (g_strcmp0(labels[i], "-") == 0) {
            buttonSub = button;
        } else if (g_strcmp0(labels[i], "*") == 0) {
            buttonMul = button;
        } else if (g_strcmp0(labels[i], "/") == 0) {
            buttonDiv = button;
        } else if (g_strcmp0(labels[i], "C") == 0) {
            buttonClear = button;
        } else if (g_strcmp0(labels[i], "=") == 0) {
            buttonEquals = button;
        }

        if (g_strcmp0(labels[i], "=") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_equals), entry);
        } else if (g_strcmp0(labels[i], "C") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clear), entry);
        } else if (g_strcmp0(labels[i], "+") == 0 || g_strcmp0(labels[i], "-") == 0 || 
                   g_strcmp0(labels[i], "*") == 0 || g_strcmp0(labels[i], "/") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(on_buttons_operations), entry);
        } else {
            g_signal_connect(button, "clicked", G_CALLBACK(on_buttons_numbers), entry);
        }
    }

    gtk_widget_show_all(window);
}