
.data

n: .word 0
h: .word 0
b: .word 0
c: .word 0
.asciiz "\n"
.asciiz "\n"
.asciiz "\n"
.asciiz "\n"
.asciiz "\n"

.text

main:
    addiu $29, $29, -8
    ori   $8, $0, 0x0
    sw    $8, 4($29)
    lui   $4, 0x1001
    lw    $4, 12($4)
    ori   $2, $0, 0x1
    syscall
    lw    $4, 0($29)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x10
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    lw    $4, 4($4)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x12
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    lw    $4, 0($4)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x14
    ori   $2, $0, 0x4
    syscall
    lui   $8, 0x1001
    lw    $8, 0($8)
    ori   $9, $0, 0x3
    addu  $8, $8, $9
    lui   $9, 0x1001
    sw    $8, 0($9)
    lui   $4, 0x1001
    lw    $4, 0($4)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x16
    ori   $2, $0, 0x4
    syscall
    lw    $8, 0($29)
    lui   $9, 0x1001
    sw    $8, 0($9)
    lui   $4, 0x1001
    lw    $4, 0($4)
    ori   $2, $0, 0x1
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x18
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    lw    $4, 8($4)
    ori   $2, $0, 0x1
    syscall
    ori   $8, $0, 0x6
    lui   $9, 0x1001
    sw    $8, 0($9)
    addiu $29, $29, 8
    ori   $2, $0, 0xa
    syscall
