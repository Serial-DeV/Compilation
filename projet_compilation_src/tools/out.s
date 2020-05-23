
.data

n: .word 2147483647
k: .word 0
.asciiz "Hello\n"
.asciiz "III\n"
.asciiz "A\n"
.asciiz "BBB"

.text

main:
    addiu $29, $29, -8
    ori   $8, $0, 0xa
    sw    $8, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 4($29)
    lui   $4, 0x1001
    lw    $4, 0($4)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x8
    ori   $2, $0, 0x4
    syscall
    lw    $4, 4($29)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0xf
    ori   $2, $0, 0x4
    syscall
    lw    $4, 0($29)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x14
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x17
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    lw    $4, 4($4)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 8
    ori   $2, $0, 0xa
    syscall
