#include "drivers/keyboard/keyboard.h"
#include "screen/screen.h"





extern void kernel_main(){
  
  //clear_screen();
  init_print();
  init_lines();
  print("hello world\n");
  print("hello from lagro after clear screen\n");
  print("hello\nagain !!\r");
  //print_at("printing in position ", 5, 3);
  clear_screen();
  put_char_at('H');
  put_char_at('L');
  put_char_at('G');
  put_char_at('P');
  put_char_at('i', .y = 1);
  put_char_at('K', 1, 1);
  put_char_at('D', .x = 5);
  put_char_at('F');
  //print_string_position("hello agaaaain ", (Cursor_Pos) { 3 , 2});
   //print("\ttesting\nnew put_char");
  // put_char('I');
  // put_char('\n');
  // put_char('T');
  clear_screen();
  while (1) {
    char c = read_key();
    if (c != 0) {
      put_char_at(c);
    }
    type_writer();
  
  }
  
}
