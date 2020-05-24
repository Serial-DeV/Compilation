
.data


.text

main:
    addiu $29, $29, -4
    ori   $8, $0, 0x7b
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 4
    ori   $2, $0, 0xa
    syscall
