#include "keyboard.h"
#include "../../hardware/ports.h"
#include "../../screen/screen.h"
char read_key(){
   
    while (1) {
      unsigned char status = inb(0x64);
      if ( status & 0x01 ) break;
    }
    unsigned char key = inb(0x60);
    if ( key & 0x80) return 0;
    // char hex[] = "0x00";
    // hex[2] = "123456789ABCDEF"[(key >> 4 ) & 0xF];
    // hex[3] = "123456789ABCDEF"[key & 0xF];
    // print(hex);
    return scan_code(key);
}

//helper function for ascci
char scan_code(unsigned char code )  {
    static char keys[128] = {
        [0x1E] = 'a',
        [0x30] = 'b',
        [0x2E] = 'c',
        [0x20] = 'd',
        [0x10] = 'q',
        [0x11] = 'w',
        [0x12] = 'e',
        [0x13] = 'r',
        [0x14] = 't',
        [0x15] = 'y',
        [0x16] = 'u',
        [0x17] = 'i',
        [0x18] = 'o',
        [0x19] = 'p',
        [0x21] = 'f',
        [0x22] = 'g',
        [0x23] = 'h',
        [0x24] = 'j',
        [0x25] = 'k',
        [0x26] = 'l',
        [0x27] = ';',
        [0x2F] = 'v',
        [0x1F] = 's',
        [0x2C] = 'z',
        [0x2D] = 'x',
        [0x31] = 'n',
        [0x32] = 'm',
        [0x02] = '1',
        [0x03] = '2',
        [0x04] = '3',
        [0x05] = '4',
        [0x06] = '5',
        [0x07] = '6',
        [0x08] = '7',
        [0x09] = '8',
        [0x0A] = '9',
        [0x0B] = '0',
        [0x1C] = '\n',
        [0x0E] = '\b',
        [0x39] = ' ',
        [0x0F] = '\t'
      };
    return keys[code];
}
