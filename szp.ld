OUTPUT_ARCH(mips)
SECTIONS
{
    .data :
    {
        *(.data*);
        *(.rodata*);
    }
    /DISCARD/ :
    {
        *(*);
    }
}
