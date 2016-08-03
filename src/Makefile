# List of make(1) rules to generate objects and binary
CFLAGS=-std=c99 -Wpedantic -Werror -Wall
INCLUDE_DIR=-I../deps/pcg/include

rng.o: rng.c rng.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c rng.c

tensor.o: tensor.c tensor.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c tensor.c
