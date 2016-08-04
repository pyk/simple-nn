CFLAGS=-std=c99 -Wpedantic -Werror -Wall

# Build the binary
bin/simple-nn: src/main.c object/tensor.o
	$(CC) $(CFLAGS) src/main.c object/tensor.o -o bin/simple-nn

# Test module
test:
	cd src; $(MAKE) rng_test
	valgrind -q --track-origins=yes --leak-check=yes ./src/rng_test
	cd src; $(MAKE) tensor_test
	valgrind -q --track-origins=yes --leak-check=yes ./src/tensor_test

