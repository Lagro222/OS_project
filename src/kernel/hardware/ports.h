#ifndef PORTS_H
#define PORTS_H

static inline unsigned char inb(unsigned short port){ // ports 65335 in total
    unsigned char result;// value from 0 to 255 
 // put the port in the d register : dx and the and al take it , result takes what in the a register a : here we have al; 
   asm volatile("inb %%dx, %%al" : "=a" (result) : "dN" (port) );  
   return result;  
}


#endif // !PORTS_H

