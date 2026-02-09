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

    mov ax, 0xB800
    mov es, ax



    ;mov di, 0
    ;mov al, 'M'
    ;mov ah, 0x4F
    ;stosw


hang:

    hlt
    jmp hang


print_string:
    lodsb
    cmp al, 0
    je done
    mov ah, 0x0E
    int 0x10
    jmp print_string

done:
    ret

print_color:
    lodsb
    cmp al,0
    je done
    mov ah, 0x04
    add di,2
    stosw

    jmp print_color

msg  db "kernel working",ENDL , 0
msg_2 db "tedting" ,0

