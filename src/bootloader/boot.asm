org 0x7C00
[bits 16]

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


 
 ;loading kernel
    mov bx, 0x8000
    mov ah, 0x02
    mov al, 10 
    int 0x13
    
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

halt:

  cli
  hlt 
  jmp halt


switch_to_pm:
  cli 
  lgdt[Gdt_descriptor]
  mov ebx, cr0
  or ebx, 1 
  mov cr0, ebx; close to protected mode

; creating GDT
Gdt_START:
    
    null_descriptor:
        dd 0
        dd 0 
    code_descriptor:
        db 0xFFFF; limit 
        dw 0      ; base 16 bits +
        db 0      ; 8 bits = 24 bits
        db 10011010; p,p,t,type flags
        db 11001111; others + limits
        db 0 ; lsst  8 bits of base 
     date_descriptor:
        db 0xFFFF
        dw 0 
        db 0 
        db 10010010; code = 0 => no
        db 11001111
        db 0

Gdt_END:

Gdt_descriptor:

   dw Gdt_END - Gdt_START -1 
   dw Gdt_START

CODE_SEG equ code_descriptor - Gdt_START
DATA_SEG equ date_descriptor - Gdt_START

call switch_to_pm

  jmp CODE_SEG:init_pm; far jump to init_pm

[bits 32]
init_pm:
  
  mov ax, DATA_SEG
  mov ds , ax
  mov fs , ax
  mov gs , ax
  mov ss , ax
  
  mov ebp, 0x90000
  mov esp, ebp

  mov ebx,welcome_pm
  call print_pm
  
  jmp 0x8000

print_pm:; helper function for 16 bits
  pusha
  mov ebx, 0x7C00
  .loop:
      mov [ebx],al
      mov ah , 0x0F
      cmp al,0
      je .done
      mov [edx],ax
      mov ebx ,1 
      mov edx , 2
      jmp .loop

  .done:
   popa 
   ret



;strings      
hello_msg db "hello from lagro v0.01",ENDL,0
error_msg db "disk error",ENDL,0
welcome_pm db "welcome to protected mode",ENDL,0 
;resevering a 512 bits
times 510 - ($ - $$) db 0

dw 0AA55h
