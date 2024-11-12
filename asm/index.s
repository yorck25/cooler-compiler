.globl _main
.align 2

function_1_5:
 mov X0, #1
 mov X16, #1
 svc 0

_main:
    adr x2, num1
    adr x3, num2
    ldrb w4, [x2]
    ldrb w5, [x3]
    sub w4, w4, #'0'
    sub w5, w5, #'0'
    add w0, w4, w5
    mov x16, #1
    svc #0x80

num1: .asciz "5"
num2: .asciz "1"
