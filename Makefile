CC = cc
CCFLAGS = $(shell pkg-config --libs --cflags sdl2)
SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
BUILD_DIR = build

.PHONY: all clean debug

all: $(BUILD_DIR)/brst

debug: CCFLAGS += -g
debug: $(BUILD_DIR)/brst

$(BUILD_DIR)/brst: $(OBJECTS)
	$(CC) -o $@ $^ $(CCFLAGS)

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm -rf $(BUILD_DIR)
