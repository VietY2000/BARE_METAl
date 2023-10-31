ENTRY(reset_handler)

MEMORY {

    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS {
    .text : {
        *(.isr_vector)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    }> FLASH
    
    .data : {
        _data = .;  
        *(.data)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss : {
        _bss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    }> SRAM

}