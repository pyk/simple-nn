# Makefile for the simple-nn project
# Run
# % make
# % make test

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
