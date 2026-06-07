# NTux-OS Userspace Application Template
# Standalone build — can be moved to any directory.
#
# Usage:
#   make                    # build myapp.elf
#   make APP_NAME=foo       # build foo.elf from src/foo.c
#   make APP_NAME=foo APP_BASE=0x12340000
#   make clean
#

CC  := cc
LD  := ld
ASM := as

CFLAGS := -std=gnu11 -O2 -g -Wall -Wextra \
          -ffreestanding -fno-stack-protector -fno-pie \
          -m64 -nostdlib -nostdinc
CPPFLAGS := -Iinclude
LDFLAGS := -m elf_x86_64 -nostdlib -static -T linker.ld

# === App configuration (override on command line) ===
APP_NAME ?= myapp
APP_BASE ?= 0x00300000

# === Libc runtime (included locally) ===
RUNTIME_C_SRC := $(wildcard libc/*.c)
RUNTIME_ASM_SRC := $(wildcard libc/*.asm)
RUNTIME_C_OBJ := $(patsubst libc/%.c,obj/libc/%.o,$(RUNTIME_C_SRC))
RUNTIME_ASM_OBJ := $(patsubst libc/%.asm,obj/libc/%.o,$(RUNTIME_ASM_SRC))
RUNTIME_OBJ := $(RUNTIME_C_OBJ) $(RUNTIME_ASM_OBJ)

OBJ_DIR := obj
OUT_DIR := out

.PHONY: all clean

all: $(OUT_DIR)/$(APP_NAME).elf

$(OUT_DIR)/$(APP_NAME).elf: obj/$(APP_NAME).o $(RUNTIME_OBJ) linker.ld
	@mkdir -p $(OUT_DIR)
	$(LD) $(LDFLAGS) --defsym=USER_BASE=$(APP_BASE) $(filter %.o,$^) -o $@
	@echo "  BUILT $(OUT_DIR)/$(APP_NAME).elf (base: 0x$$(printf '%X' $(APP_BASE)))"

obj/$(APP_NAME).o: src/$(APP_NAME).c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

obj/libc/%.o: libc/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

obj/libc/%.o: libc/%.asm
	@mkdir -p $(dir $@)
	$(ASM) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)
