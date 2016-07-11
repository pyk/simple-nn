CFLAGS=-std=c99 -Wpedantic -Werror -Wall

# Build the binary
.PHONY: build
bin/simple-nn: src/main.c object/tensor.o
	$(CC) $(CFLAGS) src/main.c object/tensor.o -o bin/simple-nn

# Test module
bin/test-tensor: src/tensor.h src/tensor.c
	mkdir -p bin
	$(CC) $(CFLAGS) -D SIMPLE_NN_TENSOR_C_TEST src/tensor.c -o bin/test-tensor
	valgrind -q --track-origins=yes --leak-check=yes ./bin/test-tensor

# Compile module as an object
object/tensor.o: src/tensor.h src/tensor.c
	mkdir -p object
	$(CC) $(CFLAGS) -c src/tensor.c -o object/tensor.o
