
.data

nb: .word 8

.text

main:
    addiu $29, $29, -4
    ori   $8, $0, 0x0
    sw    $8, 4($29)
    ori   $9, $0, 0x3
    ori   $10, $0, 0x6
    addu  $9, $9, $10
    sw    $9, 0($29)
    lw    $4, 4($29)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 4
    ori   $2, $0, 0xa
    syscall
