#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

typedef struct {
    int x;
    int y;
}Cursor_Pos ;

void print(char* vga);
void clear_screen();
void init_print();
void print_at(char* vga, int row , int col);
void put_char(char c);
void print_string_position(char* str,Cursor_Pos cur_pos);
void put_char_at_(char c, Cursor_Pos cur_pos);
#define put_char_at(c, ...) put_char_at_(c , ( Cursor_Pos ) { __VA_ARGS__}) 

#endif
