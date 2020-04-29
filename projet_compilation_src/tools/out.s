
.data

.asciiz "TEST"

.text

main:
    addiu $29, $29, -4
    ori   $8, $0, 0xa
    sw    $8, 0($29)
    lui   $4, 0x1001
    ori   $4, $4, 0x0
    ori   $2, $0, 0x4
    syscall
    addiu $29, $29, 4
    ori   $2, $0, 0xa
    syscall
