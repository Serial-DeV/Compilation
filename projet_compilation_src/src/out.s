
.data

pp: .word 0

.text

main:
    addiu $29, $29, -4
    ori   $8, $0, 0x0
    sw    $8, 4($29)
    addiu $29, $29, 4
    ori   $2, $0, 0xa
    syscall
