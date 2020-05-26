
.data

n: .word 8

.text

main:
    addiu $29, $29, 0
    lw    $4, 0($29)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 0
    ori   $2, $0, 0xa
    syscall
