CFLAGS = -Wall

all: test

test: string.c test.c elements/*
	$(CC) $(CFLAGS) -g string.c test.c -o test

.PHONY: clean
clean:
	rm -f test
