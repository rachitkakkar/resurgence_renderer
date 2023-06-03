CC = g++
DIR = .
OUTPUT_DIR = $(DIR)/build
BINARY = $(OUTPUT_DIR)/RachitTracer
STD = c++20
FILES = $(DIR)/$(wildcard *.cpp)
INCLUDE_DIR = $(DIR)/include
LIB_DIR = $(DIR)/lib
LIB_FLAGS = -lSDL2-2.0.0 -lSDL2 -lSDL2main -lSDL2_image

all:
	@$(CC) $(FILES) -o $(BINARY) -I"$(INCLUDE_DIR)" -L"$(LIB_DIR)" -std=$(STD) $(LIB_FLAGS)

clean:
	@rm $(BINARY)
	@rm *.png