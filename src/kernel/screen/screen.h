#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

void print(char* vga);
void clear_screen();
void init_print();
void print_at(char* vga, int row , int col);
void put_char(char c);

#endif
