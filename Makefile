CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O3
LD=$(CC)
LDFLAGS=-lm
DEPFLAGS=-MMD -MP

CONVERT=pnmtopng

VALGRIND=valgrind
VALGRIND_PARAMS=--tool=memcheck --leak-check=yes --track-origins=yes
VALGRIND_OUTPUT=output.log

SRC=src
SRCS=$(wildcard $(SRC)/*.c)
BUILD_DIR=build
OBJS=$(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS=$(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.d,$(SRCS))

BIN=raykat
IMAGE=image

all: $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

.PHONY: clean run image log

clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/$(BIN)
	@$<

log: $(BUILD_DIR)/$(BIN)
	$(VALGRIND) $(VALGRIND_PARAMS) --log-file=$(VALGRIND_OUTPUT) $<

image: $(BUILD_DIR)/$(BIN)
	@$< > $(IMAGE).ppm
	$(CONVERT) $(IMAGE).ppm > $(IMAGE).png
