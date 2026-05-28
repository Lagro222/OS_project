org 0x7C00
[bits 16]

%define ENDL 0x0D,0x0A

CODE_SEG equ 0x08
DATA_SEG equ 0x10

BOOT_DRIVER db 0
start:
       
    cli ; stop interuping
    xor ax,ax ; ax = 0
    mov ds, ax
    mov es ,ax
    mov ss,ax 
    mov sp,0x7C00 ;stack start from 0x7C00
    
    sti
    
    mov [BOOT_DRIVER], dl

    ;clear screen
    mov ax,0x0003
    int 0x10

     mov si, hello_msg
     call print_16

 load_kerel:
 ;loading kernel
    mov ax, 0x1000
    mov es,ax
    
    xor bx, bx ; bx = 0
     
    mov ah, 0x02 ; sectors function
    mov al,10 ; reserve 10 sectors
    mov ch, 0
    mov cl, 2 ;sector 2 (1 for bootloader)
    mov dh, 0
    mov dl ,[BOOT_DRIVER]
    
    int 0x13
    jc disk_error

    mov si,welcome_pm
    call print_16

switch_to_pm:
  cli 
  lgdt[Gdt_descriptor]
  mov eax, cr0
  or eax, 1 
  mov cr0, eax; close to protected mode
  
  jmp CODE_SEG:init_pm
; creating GDT



Gdt_START:
    
    null_descriptor:
        dd 0
        dd 0 
    code_descriptor:
        dw 0xFFFF; limit 
        dw 0      ; base 16 bits +
        db 0      ; 8 bits = 24 bits
        db 10011010b; p,p,t,type flags
        db 11001111b; others + limits
        db 0 ; lsst  8 bits of base 
     date_descriptor:
        dw 0xFFFF
        dw 0 
        db 0 
        db 10010010b; code = 0 => no
        db 11001111b
        db 0

Gdt_END:

Gdt_descriptor:

   dw Gdt_END - Gdt_START - 1 
   dd Gdt_START

;CODE_SEG equ code_descriptor - Gdt_START
;DATA_SEG equ date_descriptor - Gdt_START


; far jump to init_pm

[bits 32]
init_pm:
  
  mov ax, DATA_SEG
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  
  mov ebp, 0x90000
  mov esp, ebp

  ;mov ebx,welcome_pm
  ;call print_pm
  ; mov byte [0xB8000 + 0x1E0] , 'L'
  ; mov byte [0xB8001 + 0x1E0] , 0x4F
  ; mov byte [0xB8002 + 0x1E0] , 'A'
  ; mov byte [0xB8003 + 0x1E0] , 0x0F
  ;
  mov ebx,protected_mode
  call print_string_32

  jmp 0x10000

halt:
  hlt
  jmp halt

print_string_32:
  pusha
  mov  edi, 0xB8000 + (3 * 80 * 2) ;address of writing
  .loop:
    mov al, [ebx];load caracter from string
    cmp al, 0
    je .done
    
    mov ah, 0x0F
    mov [edi], ax
    
    inc ebx
    add edi ,2
    jmp .loop
   

  .done:
      popa
      ret

[bits 16]
print_16:; helper function for 16 bits
  pusha
  .loop:
      lodsb
      cmp al, 0
      je .done
      mov ah, 0x0E
      mov bh , 0
      int 0x10
      jmp .loop

  .done:
   popa 
   ret

disk_error:
  mov si, error_msg
  call print_16
  jmp $

;strings      
hello_msg db "hello from lagro v0.01",ENDL,0
error_msg db "disk error",ENDL,0
welcome_pm db "welcome to protected mode",ENDL,0
protected_mode db "protected mode working !!",ENDL,0
;resevering a 512 bits
times 510 - ($ - $$) db 0

dw 0AA55h
