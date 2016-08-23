CFLAGS=-std=c99 -pedantic -Werror -Wall

default: deps
.PHONY: default

# Dependencies
deps:
	$(MAKE) --directory=deps/
.PHONY: deps

# Test module
test:
	$(MAKE) test --directory=src/
.PHONY: test
