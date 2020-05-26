
.data

b: .word 5
c: .word 1

.text

main:
    addiu $29, $29, 0
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    addiu $29, $29, 0
    ori   $2, $0, 0xa
    syscall
