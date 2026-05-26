[bits 32]



global _start
_start:
  mov byte [0xB8005],'V'
  mov byte [0xB8006], 0x0F
 
