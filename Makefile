BUILD := build
OBJECTS := $(BUILD)/art.o $(BUILD)/util.o $(BUILD)/canvas.o $(BUILD)/trekscii.o
# HEADERS := include/trekscii.h
CC := g++
CV := -std=c++11

all: compile
compile: setup $(OBJECTS)
	$(CC) $(CV) $(OBJECTS) -o bin/trekscii

$(BUILD)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CV) $< -c -o $@

setup:
	mkdir -p build bin

install:
	@install -m 0755 bin/trekscii /usr/local/bin
