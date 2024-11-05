#is only working with a CMake Run/Debug configuration
cd ../output || exit

as  output.s -o output.o
ld output.o -o output

echo "Successfully compiled"

./output

echo "\nexit code "$?