org 0x7C00
bits 16

%define ENDL 0x0D,0x0A

start:

    mov ax,0x0003
    int 0x10
   ; stop intureping
    cli

    mov ax,0x9000
    mov ss, ax
    mov sp,0xFFFF

    sti  ;interuping back again

    mov si, hello_msg


print_char:
  lodsb
  cmp al,0
  je wait_key
  mov ah, 0x0E
  mov bh, 0x00
  mov bl, 0x0D
  int 0x10
  jmp print_char

wait_key:
 ;loading kernel
  mov ax, 0x0000
  mov es, ax
  mov bx , 0x8000
  mov ah,0x02
  mov al,1
  mov ch,0
  mov cl,2
  mov dh,0
  int 0x13
  jmp 0x0000:0x8000


.halt:

  cli
  hlt
  jmp .halt

hello_msg db "hello from lagro v0.01",ENDL,0
key db 0


times 510 - ($ - $$) db 0

dw 0AA55h
