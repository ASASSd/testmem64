CFLAGS=-march=native -O2 -fstack-protector -v
CC=gcc $(CFLAGS)

SRC=testmem64.c
BIN=testmem64

testmem64:
	$(CC) $(SRC) -o $(BIN)

clean:
	rm $(BIN)

install:
	cp $(BIN) /usr/bin/

uninstall:
	rm /usr/bin/$(BIN)
