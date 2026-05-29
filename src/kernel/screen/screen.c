#include "screen.h"
#include <stdbool.h>

char* vga = (char*)0xB8000 ;
int current_line = 0;
int cursor_x= 0;
int cursor_y = 0;
// bool is_control_char = true;
// bool is_newline = false;

void init_print(){
     
  for (int i = 0; i < 25; i++) {
      char* line_pos = vga + ( i * 80 * 2 );
      if( line_pos[0] == ' ' || line_pos[1] == 0 ){
        current_line = i ;
        return;
      }
      
  }
  current_line = 0 ;

}

// void put_blank( int row , int column){
//     char* vga_at = vga + ( row * 80 + column) * 2;
//     vga_at[0] = ' ';
//     vga_at[1] = 0 ; 
// }
//

bool control_char(char c){
    
  switch (c) {
      case '\n':
        cursor_y++;
        cursor_x = 0 ;
        return true;
      case '\t':
          cursor_x += 4;
          return true;
      case '\r':
        cursor_x = 0;
        return true;
      case '\b':
        if ( cursor_x > 0 ) cursor_x--;
        return true;
      default:
        return false;
    }
    
}


void put_char(char c){
          
    if(control_char(c)) return;
    char* vga_at =  vga + ( ( cursor_y * 80 + cursor_x ) * 2 ) ;
    vga_at[0] = c;
    vga_at[1] = 0x0F;
    cursor_x++;
          
    if (cursor_x >= 80 ){ 
            cursor_y++;
            cursor_x = 0;
    }



}

bool is_clear(char* vga_at){
  if ( vga_at[0] == ' ' || vga_at[1] == 0 ) return true;
  return false;
}

void print_string_position(char* str,char* vga_pos){
  int i = 0;
   
  while (str[i] != '\0') {
      vga_pos[i*2]  = str[i];
      vga_pos[i*2 + 1] = 0x0F;
      i++;
  }
}

void print_at(char* str, int row, int col){
   char* vga_pos = vga + ( ( row * 80 + col) * 2);
   if (is_clear(vga_pos)) print_string_position(str,vga_pos);
}


void print(char *str){
        char* vga_pos = vga + ( current_line * 80 * 2);
       print_string_position(str,vga_pos);
       current_line++; 
}

void clear_screen(){
  
    for(int i = 0 ; i < 24 ; i++ ){
      for (int j = 0; j < 79 ; j++) {
        
        char* vga_clr = vga + (i * 80 + j) * 2;
        vga_clr[0] = ' ';
        vga_clr[1] = 0x00;
      }
    }
    
}
