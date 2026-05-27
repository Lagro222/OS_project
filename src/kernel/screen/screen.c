#include "screen.h"

char *vga = (char*)0xB8000;

void print(char *str){
  char *show_str = vga + ( 5 * 160);
    int i = 0;
  
  while (str[i] != '\0') {
      show_str[i*2]  = str[i];
      show_str[i*2 + 1] = 0x0F;
      i++;
  }
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
