CC        := gcc
NASM      := nasm

CFLAGS    := -O0 -g3 \
             -ffreestanding -fno-builtin -fno-stack-protector -fno-omit-frame-pointer -nostdinc \
             -Iinclude \
             -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion \
             -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion \
             -Wno-switch -Wno-conversion -Wno-unused-but-set-variable

DEPFLAGS = -MMD -MP -MF $(basename $@).d

LDFLAGS   := -nostdlib -static -Wl,-e,_start

BUILD_DIR := build
SRC_DIR   := src
TEST_DIR  := test

SRC_C   := $(shell find $(SRC_DIR) -type f -name '*.c')
SRC_ASM := $(shell find $(SRC_DIR) -type f -name '*.s')

OBJ_C   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_C))
OBJ_ASM := $(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/%.o,$(SRC_ASM))
OBJ_ALL := $(OBJ_C) $(OBJ_ASM)

DEPS := $(OBJ_C:.o=.d)

START_SRC := $(SRC_DIR)/start.s
START_OBJ := $(BUILD_DIR)/start.o

LIBDIR  := $(BUILD_DIR)/lib
LIBNAME := libc.a
LIB     := $(LIBDIR)/$(LIBNAME)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test/%,$(TEST_SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test/%.o,$(TEST_SRCS))

.PHONY: all lib test clean run

all: lib test

lib: $(LIB)

LIB_OBJS := $(filter-out $(START_OBJ), $(OBJ_ALL))

$(LIB): $(LIB_OBJS) | $(LIBDIR)
	@mkdir -p $(dir $@)
	@printf "\033[1;36m[AR]\033[0m %s\n" "$@"
	ar rcs $@ $(LIB_OBJS)
	@ranlib $@ || true

test: $(LIB) $(START_OBJ) $(TEST_BINS)
	@printf "\033[1;34m[TEST]\033[0m All test binaries built.\n"

$(BUILD_DIR)/test/%: $(LIB) $(START_OBJ) $(BUILD_DIR)/test/%.o
	@printf "\033[1;33m[LD]\033[0m %s\n" "$@"
	$(CC) $(LDFLAGS) -o $@ $(START_OBJ) $(BUILD_DIR)/test/$*.o $(LIB)

$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@printf "\033[1;32m[CC]\033[0m %s\n" "$<"
	$(CC) $(CFLAGS) -c $< -o $@

run: test
	@for bin in $(TEST_BINS); do \
		printf "\033[1;35m[RUN]\033[0m %s\n" "$$bin"; \
		./$$bin; \
		ec=$$?; \
		if [ $$ec -ne 0 ]; then \
			printf "\033[1;31m[FAIL]\033[0m %s exited with code %d\n" "$$bin" "$$ec"; \
			exit $$ec; \
		else \
			printf "\033[1;32m[PASS]\033[0m %s\n" "$$bin"; \
		fi; \
	done

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@printf "\033[1;32m[CC]\033[0m %s\n" "$<"
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@printf "\033[1;35m[ASM]\033[0m %s\n" "$<"
	$(NASM) -f elf64 $< -o $@

$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -rf $(BUILD_DIR)

crun: clean run

-include $(DEPS)
