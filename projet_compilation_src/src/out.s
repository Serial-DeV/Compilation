
.data

n: .word 217
k: .word 0
.asciiz "Hello\n"

.text

main:
    addiu $29, $29, -4
    ori   $8, $0, 0x14
    sw    $8, 8($29)
    lui   $4, 0x1001
    lw    $4, 0($4)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x8
    ori   $2, $0, 0x4
    syscall
    lw    $4, 8($29)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 4
    ori   $2, $0, 0xa
    syscall
