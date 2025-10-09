#include <gtk/gtk.h>
#include "operations.h"
#include "string.h"

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
};

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

g_signal_connect(buttonClean, "clicked", G_CALLBACK(on_button_clean), entry);

void on_button_clean(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    gtk_entry_set_text(entry, "");
}

g_signal_connect(buttonEquals, "clicked", G_CALLBACK(on_button_equals), entry);

void on_button_equals(GtkWidget *widget, gpointer data){
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *current = gtk_entry_get_text(entry);
    char op[4] = { '+', "-", "/", "*"};
    int 
    for(int i = 0; i < 4; i++){
        char x = op[i];
        char *pos = strchr(current, x);
        if(pos){
            int op_index = pos - current;
            char left[op_index + 1];
            strncpy(left, current, op_index);
            left[op_index] = '\0';
            const char *right = pos + 1;
            double a = atoi(left);
            double b = atoi(right);
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
            sprintf(result_str, "%d", result);
            gtk_entry_set_text(entry, result_str);
        }
    }
}