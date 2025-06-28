ENTRY(__start)
SECTIONS {
    . = 0x80001500;
    .text : {
        *(.init.s)
        *(.text*)
    }
    .rodata : {
        *(.rodata*)
    }
    .data : {
        *(.data*)
    }
    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        _end = .;
    }
}
