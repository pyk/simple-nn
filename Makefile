CFLAGS=-std=c99 -Wpedantic -Werror -Wall

default:
	@echo "Nothing happen yet"

# Test module
test: test-rng test-tensor

test-rng:
	$(MAKE) rng_test --directory=src/
	valgrind -q --track-origins=yes --leak-check=yes ./src/rng_test
.PHONY: test-rng

test-tensor:
	$(MAKE) tensor_test --directory=src/
	valgrind -q --track-origins=yes --leak-check=yes ./src/tensor_test
.PHONY: test-tensor
