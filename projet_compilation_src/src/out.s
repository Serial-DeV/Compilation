
.data

n: .word 217

.text

main:
    addiu $29, $29, 0
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    ori   $8, $0, 0x5
    ori   $9, $0, 0x7
    addu  $8, $8, $9
    lw    $4, 0($29)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 0
    ori   $2, $0, 0xa
    syscall
