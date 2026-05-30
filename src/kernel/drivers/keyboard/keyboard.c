#include "keyboard.h"

//### TODO : connecting with the keyboard at the port 0x80 

unsigned char inbyte(unsigned short port){
    unsigned char result;
 // put the port in the d register : dx and the and al take it , result takes what in the a register a : here we have al; 
   asm("in %%dx, %%al" : "=a" (result) : "d" (port) );
  
   return result;
  
}
