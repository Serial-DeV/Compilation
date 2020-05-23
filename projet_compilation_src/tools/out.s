
.data

.asciiz "Hello"
.asciiz "Hello"
.asciiz "HI"
.asciiz "HI"
.asciiz "HI"

.text

main:
    addiu $29, $29, 0
    lui   $4, 0x1001
    ori   $4, $4, 0x0
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x6
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0xc
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0xf
    ori   $2, $0, 0x4
    syscall
    lui   $4, 0x1001
    ori   $4, $4, 0x12
    ori   $2, $0, 0x4
    syscall
    addiu $29, $29, 0
    ori   $2, $0, 0xa
    syscall
