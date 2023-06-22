CFLAGS=-march=native -O2 -fstack-protector -Werror
CC=gcc

SRC=testmem64.c
BIN=testmem64

BUILD_DIR=./build
INSTALL_PATH=/usr/bin
DISASM_DIR=./disasm
DISASM_FILE=$(BIN)_disasm.txt

.PHONY: build run clean install uninstall strip disasm

build:
	@printf "\tMKDIR\t$(BUILD_DIR)\n\r"
	@mkdir -p $(BUILD_DIR)
	@printf "\tCC\t$(SRC)\n\r"
	@$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/$(BIN)

run:
	@printf "\tRUN\n\r"
	@$(BUILD_DIR)/$(BIN)
	
clean:
	@printf "\tCLEAN\t$(BUILD_DIR) $(DISASM_DIR)\n\r"
	@rm -rf $(BUILD_DIR) $(DISASM_DIR)
strip:
	@printf "\tSTRIP\t./build/$(BIN)\n\r"
	@strip $(BUILD_DIR)/$(BIN)

install:
	@printf "\tINSTALL\t$(INSTALL_PATH)\n\r"
	@cp $(BUILD_DIR)/$(BIN) $(INSTALL_PATH)

uninstall:
	@printf "\tUNINSTALL\t$(INSTALL_PATH)\n\r"
	@rm $(INSTALL_PATH)/$(BIN)

disasm:
	@printf "\tMKDIR\t$(DISASM_DIR)\n\r"
	@mkdir -p $(DISASM_DIR)
	@touch $(DISASM_DIR)/$(DISASM_FILE)
	@printf "\tDISASM\t$(DISASM_FILE)\n\r"
	@file $(BUILD_DIR)/$(BIN) > $(DISASM_DIR)/$(DISASM_FILE)
	@readelf -W -a $(BUILD_DIR)/$(BIN) >> $(DISASM_DIR)/$(DISASM_FILE)
	@objdump -d -S $(BUILD_DIR)/$(BIN) >> $(DISASM_DIR)/$(DISASM_FILE)
