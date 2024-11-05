.globl _main
.align 2

function_1_5:
 mov X0, #1
 mov X16, #1
 svc 0

_main:
    b function_1_5

myVar:
    .string "chat"