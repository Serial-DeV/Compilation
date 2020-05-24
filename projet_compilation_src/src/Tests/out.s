
.data

test: .word 3
test2: .word 1
test3: .word 456

.text

main:
    addiu $29, $29, -12
    ori   $8, $0, 0x0
    sw    $8, 12($29)
    ori   $8, $0, 0x0
    sw    $8, 16($29)
    ori   $8, $0, 0x6
    sw    $8, 20($29)
    addiu $29, $29, 12
    ori   $2, $0, 0xa
    syscall
