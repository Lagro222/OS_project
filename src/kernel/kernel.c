#include "screen/screen.h"

extern void kernel_main(){
  
  //clear_screen();
  init_print();
  print("hello world\n");
  print("hello from lagro after clear screen\n");
  print("hello\nagain !!\r");
  print_at("printing in position ", 6, 3);
  // clear_screen();
  // put_char('H');
  // put_char('I');
  // put_char('\n');
  // put_char('T');
  while (1) { }
}
