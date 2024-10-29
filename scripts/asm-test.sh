as -o asm/index.o asm/index.s

ld -o asm/index asm/index.o

echo "Successfully compiled"

open asm/index

echo $?