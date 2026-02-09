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
    call print_string


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

    jc disk_error

    jmp 0x0000:0x8000

print_string:

  lodsb
  cmp al,0
  je .done
  mov ah, 0x0E
  mov bh, 0x00
  mov bl, 0x0D
  int 0x10
  jmp print_string

.done:
    ret

disk_error:
    mov si, error_msg
    call print_string
    jmp .halt


.halt:

  cli
  hlt
  jmp .halt

hello_msg db "hello from lagro v0.01",ENDL,0
error_msg db "disk error",ENDL,0


times 510 - ($ - $$) db 0

dw 0AA55h
