#include "ports.h"

unsigned char inb(unsigned short port){ // ports 65335 in total
    unsigned char result;
 // put the port in the d register : dx and the and al take it , result takes what in the a register a : here we have al; 
   asm("in %%dx, %%al" : "=a" (result) : "d" (port) );  
   return result;
  
}
