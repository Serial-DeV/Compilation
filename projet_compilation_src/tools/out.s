
.data


.text

main:
    addiu $29, $29, -4
    ori   $8, $0, 0x2
    sw    $8, 0($29)
    ori   $8, $0, 0x3
    sw    $8, 0($29)
    addiu $29, $29, 4
    ori   $2, $0, 0xa
    syscall
