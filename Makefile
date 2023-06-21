CFLAGS=-march=native -O2 -fstack-protector -v -Werror
CC=gcc $(CFLAGS)

SRC=testmem64.c testmem64.h
BIN=testmem64

.PHONY: build run clean install uninstall strip disasm

build:
	mkdir -p ./build
	$(CC) $(SRC) -o ./build/$(BIN)

run:
	./build/$(BIN)
	
clean:
	rm -rf ./build ./disasm

strip:
	strip ./build/$(BIN)

install:
	cp ./build/$(BIN) /usr/bin/

uninstall:
	rm /usr/bin/$(BIN)

disasm:
	mkdir -p ./disasm
	touch ./disasm/disasm_report.txt
	readelf -W -a ./build/$(BIN) > ./disasm/disasm_report.txt
	objdump -d -S ./build/$(BIN) >> ./disasm/disasm_report.txt
