# Makefile to build the src objects and test the module

CFLAGS=-std=c99 -pedantic -Werror -Wall
INCLUDE_DIR=-I../deps/pcg/include
LIBRARY_DIR=-L../deps/pcg/src

# Modules & their test
rng.o: rng.c rng.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c rng.c

rng_test: rng.c rng.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(LIBRARY_DIR) \
		-D SIMPLE_NN_RNG_C_TEST -o rng_test rng.c -lpcg_random -lm

test-rng: rng_test
	valgrind -q --track-origins=yes --leak-check=yes ./rng_test
.PHONY: test-rng

tensor.o: tensor.c tensor.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c tensor.c

tensor_test: tensor.c tensor.h rng.o
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(LIBRARY_DIR) \
		-D SIMPLE_NN_TENSOR_C_TEST -o tensor_test tensor.c rng.o \
		-lpcg_random -lm

test-tensor: tensor_test
	valgrind -q --track-origins=yes --leak-check=yes ./tensor_test
.PHONY: test-tensor

# Test target
test: test-rng test-tensor
