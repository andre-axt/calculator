Simple calculator with Gtk interface

gcc main.c interface.c operations.c -o calculator `pkg-config --cflags --libs gtk+-3.0`