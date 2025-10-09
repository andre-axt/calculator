#include <gtk/gtk.h>
#include "stdio.h"
#include "operations.h"
#include "interface.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    create_calculator_window();
    gtk_main();
    return 0;
}