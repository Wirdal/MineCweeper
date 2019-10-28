# Usage:
# make 			# compile all binary
# make debug	# Compile binary for debug utilities
# make clean	# remove binary

.DEFAULT_GOAL := make

CC=gcc

make: main.c
	$(CC) main.c -o main.exe

deubg:
	$(CC) main.c -ggdb -o main.exe

clean:
	rm *.exe