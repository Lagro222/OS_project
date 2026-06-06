#include "screen.h"
#include <stdbool.h>
#include <stddef.h>

char* vga = (char*)0xB8000 ;
int current_line = 0;
int cursor_x = 0;
int cursor_y = 0;
static int blinking = 100;
static int count = 0;
static bool cur_visible = true;
//bool cur_moving = true;
Line lines[MAX_LINES];  
Line *cur_line ;

void init_print(){
     
  for (int i = 0; i < 25; i++) {
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
        cur_line->last_x = cursor_x;
        cur_line  = &lines[next];
        cursor_y++;
        cursor_x = 0;
    }

}

bool control_char(char c){

 switch (c) {
      case '\n': 
        on_newline();
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
    
}



void put_char(char c){
  
  if (control_char(c)) return;

  char* vga_at = vga + (cursor_y * 80 + cursor_x ) * 2;
  vga_at[0] = c;
  vga_at[1] = 0x0F;
  cursor_x++;
}

// void show_cursor(){       
//   if (cur_visible) {
//            put_char_at('_');
//   }
// }
//
// void hide_cursor(){
//   if (!cur_visible) {
//   put_char_at(' ');
//   }
// }
void type_writer(){  


  if (count > blinking) {
      cur_visible = !cur_visible;
      count = 0;
  }

  if (cur_visible) {
      put_char('_');
  }else {
      put_blank(cursor_y , cursor_x - 1 );
  }
         
    
}


void put_char_at(char c,int x , int y){
    
    if(control_char(c)) return;
    
    char* vga_at = vga + ( y * 80 + x) * 2;
    vga_at[0] = c;
    vga_at[1] = 0x0F;
  
      
    if (cursor_x >= 80 ){ 
            cursor_y++;
            cursor_x = 0;
    }

}

bool is_clear(char* vga_at){
  if ( vga_at[0] == ' ' || vga_at[1] == 0 ) return true;
  return false;
}

void print_string_position(char* str,Cursor_Pos cur_pos){
  int i = 0;
   
  while (str[i] != '\0') {
      put_char_at(str[i], cur_pos.x , cur_pos.y );
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
  
    for(int i = 0 ; i < 24 ; i++ ){
      for (int j = 0; j < 80 ; j++) {
        put_blank(i, j);          
      }
    }
    cursor_x = 0 ;
    cursor_y = 0 ;
    
}
