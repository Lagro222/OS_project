#include "screen/screen.h"

extern void kernel_main(){
  
  //clear_screen();
  init_print();
  print("hello world");
  print("hello from lagro after clear screen");
  print("hello again !!");
  print_at("printing in position ", 6, 3);
  while (1) { }
}
