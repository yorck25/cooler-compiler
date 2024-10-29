as -o asm/index.o asm/index.s
ld asm/index.o -o asm/index

echo "Successfully compiled"

./asm/index

echo "\nexit code "$?