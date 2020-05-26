
.data

n: .word 1
o: .word 0

.text

main:
    addiu $29, $29, 0
    lui   $8, 0x1001
    lw    $8, 0($8)
    lui   $9, 0x1001
    lw    $9, 4($9)
    div   $8, $9
    teq $9, $0
    mfhi  $8
    lui   $9, 0x1001
    sw    $8, 0($9)
    lui   $4, 0x1001
    lw    $4, 0($4)
    ori   $2, $0, 0x1
    syscall
    addiu $29, $29, 0
    ori   $2, $0, 0xa
    syscall
