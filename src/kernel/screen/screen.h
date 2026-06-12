#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

//TYPEDEFS
typedef struct Line{
    int last_x;
    int line_number;
    char str[81];
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
bool run_cmd(char* str);
void clear_screen();
void type_writer();
//STRING PRITING
void print(const char* vga);
void print_at(char* vga, int row , int col);
void print_string_position(char* str,int row , int column);
void myprintf(const char *vga,...);
//CHARACTER PUTS
void put_char(char c);
void put_char_at(char c, int x , int y);
void print_color(char c , char color);


#endif
