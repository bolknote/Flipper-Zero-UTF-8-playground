CFLAGS = -Wall -g

all: test

test: string.c test.c elements/* includes/*.h
	$(CC) $(CFLAGS) string.c test.c -o test

.PHONY: clean
clean:
	rm -f test
