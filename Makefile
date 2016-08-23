CFLAGS=-std=c99 -pedantic -Werror -Wall

default: deps
.PHONY: default

# Dependencies
deps: deps/pcg/src/libpcg_random.a
.PHONY: deps

deps/pcg/src/libpcg_random.a:
	$(MAKE) --directory=deps/pcg/

# Test module
test: test-rng test-tensor

test-rng: deps/pcg/src/libpcg_random.a
	$(MAKE) rng_test --directory=src/
	valgrind -q --track-origins=yes --leak-check=yes ./src/rng_test
.PHONY: test-rng

test-tensor: deps/pcg/src/libpcg_random.a
	$(MAKE) tensor_test --directory=src/
	valgrind -q --track-origins=yes --leak-check=yes ./src/tensor_test
.PHONY: test-tensor
