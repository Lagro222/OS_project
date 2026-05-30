#include "screen/screen.h"

extern void kernel_main(){
  
  //clear_screen();
  init_print();
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
  put_char_at('K', .y = 2);
   print("\ttesting\nnew put_char");
  // put_char('I');
  // put_char('\n');
  // put_char('T');
  while (1) { }
}
