CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Werror -pedantic
.PHONY: test clean
test: test_geometry
	./test_geometry
test_geometry: test_geometry.c ../include/sfsnext_io.h ../include/sfsnext_disk.h
	$(CC) $(CFLAGS) -o $@ test_geometry.c
clean:
	rm -f test_geometry
