ENTRY(_start)

SECTIONS
{
  . =0x10000;

  .text : {
      *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {

   *(.data*) 
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }

 /DISCARD/ : {
  *(.note.GNU-stack)
  *(.gnu_eh_frame)
  *(.gnu.hash)
 }
}

