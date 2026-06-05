#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

//TYPEDEFS
typedef struct Line{
    int last_x;
    int line_number;
    struct Line *previous;
}Line;

#define MAX_LINES 25

extern Line lines[MAX_LINES];
extern Line *cur_line;

typedef struct {
    int x;
    int y;
}Cursor_Pos ;


//INITS
void init_print();
void init_lines();
//ADDITIONS
void clear_screen();
void type_writer();
//STRING PRITING
void print(char* vga);
void print_at(char* vga, int row , int col);
void print_string_position(char* str,Cursor_Pos cur_pos);

//CHARACTER PUTS
void put_char(char c);
void put_char_at_(char c, Cursor_Pos cur_pos);
#define put_char_at(c, ...) put_char_at_(c , ( Cursor_Pos ) { __VA_ARGS__}) 
void print_color(char c , char color);


#endif
