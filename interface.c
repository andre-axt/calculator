#include <gtk/gtk.h>
#include "operations.h"
#include "string.h"
#include <stdlib.h>
#include <ctype.h>

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

double evaluate_expression(const char *expr) {
    char tokens[50][16]; 
    int token_count = 0;
    int i = 0, j = 0;
    char current_token[16] = "";
    while (expr[i] != '\0') {
        if (isdigit(expr[i]) || expr[i] == '.') {
            current_token[j++] = expr[i];
        } else {
            if (j > 0) {
                current_token[j] = '\0';
                strcpy(tokens[token_count++], current_token);
                j = 0;
            }
            tokens[token_count][0] = expr[i];
            tokens[token_count][1] = '\0';
            token_count++;
        }
        i++;
    }

    if (j > 0) {
        current_token[j] = '\0';
        strcpy(tokens[token_count++], current_token);
    }

    for (int i = 0; i < token_count; i++) {
        if (strcmp(tokens[i], "*") == 0 || strcmp(tokens[i], "/") == 0) {
            double a = atof(tokens[i - 1]);
            double b = atof(tokens[i + 1]);
            double result;

            if (strcmp(tokens[i], "*") == 0) {
                result = mul(a, b);
            } else {
                result = divide(a, b);
            }

            sprintf(tokens[i - 1], "%.10f", result);

            for (int j = i; j < token_count - 2; j++) {
                strcpy(tokens[j], tokens[j + 2]);
            }

            token_count -= 2;
            i--; 
        }
    }

    double result = atof(tokens[0]);

    for (int i = 1; i < token_count; i += 2) {
        double next = atof(tokens[i + 1]);

        if (strcmp(tokens[i], "+") == 0) {
            result = add(result, next);
        } else if (strcmp(tokens[i], "-") == 0) {
            result = sub(result, next);
        }
    }

    return result;
}

void on_button_equals(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *current = gtk_entry_get_text(entry);
    double result = evaluate_expression(current);
    char result_str[32];
    sprintf(result_str, "%.2f", result);
    gtk_entry_set_text(entry, result_str);

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