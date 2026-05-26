void print(char *str){
  
  char *vga = (char*)0xB8000 + ( 5 * 160) ;
  int i = 0;

  while (str[i] != '\0') {
      vga[i*2] = str[i];
      vga[i*2 + 1] = 0x0F;
      i++;
  }
}

extern void kernel_main(){

  print("hello world");
  while (1) { }
}
