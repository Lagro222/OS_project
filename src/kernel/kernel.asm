org 0x8000

bits 16

%define ENDL 0x0D,0x0A

start:

    cli

    mov ax, 0x0000
    mov ds, ax
    mov es, ax

    mov ax ,0x9000
    mov ss, ax
    mov sp,0xFFFF

    sti


    mov si, msg
    call print_string

    ;enable cursor
    mov al, 0x01
    mov cx, 0x0607
    int 0x10

 command_loop:
    mov si, prompt
    call print_string

    call read_key

    ;echo the caracter
    mov ah,0x0E
    int 0x10

    ;newline
    mov al,0x0D
    int 0x10
    mov al,0x0A
    int 0x10

    jmp command_loop

read_key:

    mov ah,0x00
    int 0x16
    ret



hang:

    hlt
    jmp hang


print_string:
    push ax
    push bx
.loop:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0x0E
    int 0x10
    jmp .loop

.done:
    pop ax
    pop bx
    ret

msg  db "kernel working",ENDL , 0
prompt db "> ", 0

