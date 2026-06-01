#include "keyboard.h"
#include "../../hardware/ports.h"

char read_key(){
   
    while (1) {
      unsigned char status = inb(0x64);
      if ( status & 0x01 ) break;
    }
    unsigned char key = inb(0x60);
    if ( key & 0x80) return 0;

    return scan_code(key);
}

//helper function for ascci
char scan_code(unsigned char code )  {
    static char keys[128] = {
        [0x1E] = 'a',
        [0x30] = 'b',
        [0x2E] = 'c',
        [0x1C] = '\n'
      };
    return keys[code];
}
