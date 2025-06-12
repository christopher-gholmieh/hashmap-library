# Written by: Christopher Gholmieh
# Flags:
COMPILER_FLAGS=-Wpedantic -Wextra -Wall -Werror


# Build:
all:
	gcc $(COMPILER_FLAGS) $(COMPILER_SOURCE) ./hashmap-test.c -o ./hashmap-test
