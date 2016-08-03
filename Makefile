CFLAGS=-std=c99 -Wpedantic -Werror -Wall

# Build the binary
bin/simple-nn: src/main.c object/tensor.o
	$(CC) $(CFLAGS) src/main.c object/tensor.o -o bin/simple-nn

# Test module
bin/test-tensor: src/tensor.h src/tensor.c object/rng.o
	mkdir -p bin
	$(CC) $(CFLAGS) -D SIMPLE_NN_TENSOR_C_TEST -Ideps/pcg/include \
		src/tensor.c object/rng.o -o bin/test-tensor \
		deps/pcg/src/libpcg_random.a -lm
	valgrind -q --track-origins=yes --leak-check=yes ./bin/test-tensor

bin/test-rng: src/rng.h src/rng.c
	mkdir -p bin
	$(CC) $(CFLAGS) -D SIMPLE_NN_RNG_C_TEST -Ideps/pcg/include \
		src/rng.c -o bin/test-rng deps/pcg/src/libpcg_random.a -lm
	valgrind -q --track-origins=yes --leak-check=yes ./bin/test-rng

