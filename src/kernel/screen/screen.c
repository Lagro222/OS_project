#include "screen.h"
#include <stdbool.h>
#include <stddef.h>
#include "../utils/string.h"
char* vga = (char*)0xB8000 ;
int current_line = 0;
int cursor_x = 0;
int cursor_y = 0;
static int blinking = 50000;
static int count = 0;
static int last_cursor_x = 0;
static int last_cursor_y = 0;

static bool cur_visible = true;
static bool in_clear = false;
// static bool is_newline = false;
//bool cur_moving = true;
Line lines[MAX_LINES];  
Line *cur_line ;

void init_print(){
     
  for (int i = 0; i < MAX_LINES; i++) {
      char* line_pos = vga + ( i * 80 * 2 );
      if( line_pos[0] == ' ' || line_pos[1] == 0 ){
        cursor_y = i ;
        return;
      }
      
  }
  cursor_y = 0 ;

}

void init_lines(){
      
  for (int i = 0; i < MAX_LINES ; i++) {
     lines[i].last_x = 0;
     lines[i].line_number = i;
     lines[i].previous = ( i > 0) ? &lines[i - 1] : NULL;
     lines[i].str[0] = '\0';
  }
  cur_line = &lines[0];
}


void put_blank( int row , int column){
    char* vga_at = vga + ( row * 80 + column) * 2;
    vga_at[0] = ' ';
    vga_at[1] = 0 ; 
}

void on_newline(){
    int next = cur_line->line_number + 1;
    if ( next < MAX_LINES) {
       //is_newline = true;
        cur_line->last_x = cursor_x;
        //cur_line->previous = &lines[cur_line->line_number];
        cur_line  = &lines[next]; 
        cursor_y++;
        cursor_x = 0;
    }

}

bool run_cmd(char* str){
  
  if(mystrcmp(str, "clear") == 0 ){
    clear_screen();
    init_lines();
    return true;
  }else if (mystrncmp(str, "echo ", 5) == 0) {
        on_newline();
        print(&str[5]);
        on_newline();
        return true;
  }else if (mystrcmp(str, "help") == 0) {
      on_newline();
      print("help // commands : clear / echo 'string' / help\n");
      return true;
  }
 return false;
}

bool control_char(char c){
     
 switch (c) {
      case '\n':
        // run_cmd(cur_line->str);
        // on_newline();
        // if (in_clear) cursor_y--;
        // in_clear = false;
        if (!run_cmd(cur_line->str)) on_newline();
        put_blank(last_cursor_x, last_cursor_y);
        return true;
      case '\t':
          cursor_x += 4;
          return true;
      case '\r':
        cursor_x = 0;
        return true;
      case '\b':
        
        if (cursor_x == 0 && cursor_y == 0) return true; 

        if(cursor_x == 0 && cur_line->previous != NULL){
            put_blank(cursor_y, cursor_x);
            cursor_y--; 
            cursor_x = cur_line->previous->last_x;
            cur_line = cur_line->previous;
         
        }
        else if (cursor_x > 0){ 

          put_blank(cursor_y, cursor_x);
          cursor_x--;  
        }
        
        //put_blank(cursor_y, cursor_x + 1);
                   
        return true;
      default:
        return false;
    }
 
//print_string_position("lagro->", cursor_y, 0);

}



void put_char(char c){
  
  if (control_char(c)) return;

  char* vga_at = vga + (cursor_y * 80 + cursor_x ) * 2;
  vga_at[0] = c;
  vga_at[1] = 0x0F;
  
  cur_line->str[cursor_x] =  c ;
  last_cursor_x = cursor_x + 1;
  last_cursor_y = cursor_y;
  cursor_x++;
  cur_line->str[cursor_x] = '\0';
}

void type_writer(){  
  
  count++;

  if (count > blinking) {
      cur_visible = !cur_visible;
      count = 0;
  }

  char *vga_at = vga + (cursor_y * 80 + cursor_x) * 2;

   if (cur_visible) {
      vga_at[0] = '_';
      vga_at[1] = 0x0F ;
  }else {
      vga_at[0] = ' ';
      vga_at[1] = 0 ;      
  }

  if (last_cursor_y != cursor_y) {
      put_blank(last_cursor_y, last_cursor_x);
  }
}


void put_char_at(char c,int x , int y){
    
    //if(control_char(c)) return;
    char* vga_at = vga + ( y * 80 + x) * 2;
    vga_at[0] = c;
    vga_at[1] = 0x0F;

}

bool is_clear(char* vga_at){
  if ( vga_at[0] == ' ' || vga_at[1] == 0 ) return true;
  return false;
}

void print_string_position(char* str,int row , int column){
  int i = 0;
   
  while (str[i] != '\0') {
      put_char_at(str[i], column + i,row  );
      i++;
  }
}


void print(char *str){
       int i = 0;
       while (str[i] != '\0') {
            put_char(str[i]);
            i++;
       }
}
// void print_number(int number){
//
//
// }
void print_color(char c , char color){
  char *vga_target = vga + (cursor_y * 80 + cursor_x)*2;
  vga_target[0] = c;
  vga_target[1] = color;
  cursor_x++;
}
void clear_screen(){
    //in_clear = true;
    for(int i = 0 ; i < MAX_LINES; i++ ){
      for (int j = 0; j < 80 ; j++) {
        put_blank(i, j);          
      }
    }
    cursor_x = 0 ;
    cursor_y = 0 ;
    
}
