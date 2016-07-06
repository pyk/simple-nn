CFLAGS=-std=c99 -Wpedantic -Werror -Wall

# Build the binary
.PHONY: build
build:
	$(CC) $(CFLAGS) src/main.c src/tensor.c -o bin/simple-nn

# Test
.PHONY: test-tensor
test-tensor:
	@echo "Test: tensor"
	$(CC) $(CFLAGS) -g src/tensor_test.c src/tensor.c -o bin/tensor-test
	valgrind -q --track-origins=yes --leak-check=yes ./bin/tensor-test
