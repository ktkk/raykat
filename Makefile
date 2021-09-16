CC=gcc
CFLAGS=-Wall -Wextra -g -std=c11
LD=$(CC)
LDFLAGS=
DEPFLAGS=-MMD -MP

SRC=src
SRCS=$(wildcard $(SRC)/*.c)
BUILD_DIR=build
OBJS=$(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS=$(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.d,$(SRCS))

BIN=raykat
IMAGE=image.ppm

all: $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

.PHONY: clean run image

clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/$(BIN)
	@$<

image: $(BUILD_DIR)/$(BIN)
	$< > $(IMAGE)
