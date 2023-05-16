CFLAGS=-march=native -O2 -fstack-protector -v
CC=gcc $(CFLAGS)

SRC=testmem64.c
BIN=testmem64

testmem64:
	mkdir ./build
	$(CC) $(SRC) -o ./build/$(BIN)

clean:
	rm -r ./build

install:
	cp ./build/$(BIN) /usr/bin/

uninstall:
	rm /usr/bin/$(BIN)
