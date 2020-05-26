
.data

n: .word 6

.text

main:
    addiu $29, $29, -4
    ori   $8, $0, 0x9
    sw    $8, 4($29)
    lui   $4, 0x1001
    lw    $4, 0($4)
    ori   $2, $0, 0x1
    syscall
    lw    $4, 4($29)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 4
    ori   $2, $0, 0xa
    syscall
