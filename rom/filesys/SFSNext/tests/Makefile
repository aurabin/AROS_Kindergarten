CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Werror -pedantic
.PHONY: test clean
test: test_geometry test_codec sfsnext_inspect
	./test_geometry
	./test_codec
	./sfsnext_inspect >/dev/null 2>&1 && exit 1 || test $$? -eq 2
test_geometry: test_geometry.c ../include/sfsnext_io.h ../include/sfsnext_disk.h
	$(CC) $(CFLAGS) -o $@ test_geometry.c
test_codec: test_codec.c ../include/sfsnext_codec.h ../include/sfsnext_io.h ../include/sfsnext_disk.h
	$(CC) $(CFLAGS) -o $@ test_codec.c
sfsnext_inspect: ../tools/sfsnext_inspect.c ../include/sfsnext_codec.h
	$(CC) $(CFLAGS) -o $@ ../tools/sfsnext_inspect.c
clean:
	rm -f test_geometry test_codec sfsnext_inspect
