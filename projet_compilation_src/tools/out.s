
.data

n: .word -4
o: .word 2147483647
q: .word -2147483648

.text

main:
    addiu $29, $29, 0
    addiu $29, $29, 0
    ori   $2, $0, 0xa
    syscall
