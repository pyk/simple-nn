# List of make(1) rules to generate objects and binary
CFLAGS=-std=c99 -Wpedantic -Werror -Wall
INCLUDE_DIR=-I../deps/pcg/include
LIBRARY_DIR=-L../deps/pcg/src

# Modules & their test
rng.o: rng.c rng.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c rng.c

rng_test: rng.c rng.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(LIBRARY_DIR) \
		-D SIMPLE_NN_RNG_C_TEST -o rng_test rng.c -lpcg_random -lm

tensor.o: tensor.c tensor.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c tensor.c

tensor_test: tensor.c tensor.h rng.o
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(LIBRARY_DIR) \
		-D SIMPLE_NN_TENSOR_C_TEST -o tensor_test tensor.c rng.o \
		-lpcg_random -lm
