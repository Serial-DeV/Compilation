
.data

n: .word 2147483647
.asciiz "Test\n"
main:
    addiu $29, $29, -8
    ori   $8, $0, 0xa
    sw    $8, 0($29)
    ori   $8, $0, 0x64
    sw    $8, 0($29)
    addiu $29, $29, 8
    ori   $2, $0, 0xa
    syscall
