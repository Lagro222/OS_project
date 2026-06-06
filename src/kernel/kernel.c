#include "drivers/keyboard/keyboard.h"
#include "screen/screen.h"
#include <stdbool.h>

static bool key_pressed = false;

extern void kernel_main(){
  
  //clear_screen();
  init_print();
  init_lines();
  print("hello world\n");
  print("hello from lagro after clear screen\n");
  //print_string_position("hello agaaaain ", (Cursor_Pos) { 3 , 2});
   //print("\ttesting\nnew put_char");
  // put_char('I');
  // put_char('\n');
  // put_char('T');
  clear_screen();
  while (1) {
    char c = read_key();
    if (c != 0) {
      if (!key_pressed) {
        put_char(c);  
        key_pressed = true;
      }
     
    }
    if (c == 0 && key_pressed) {
        key_pressed = false;
    }
   type_writer();
  
  }
  
}
