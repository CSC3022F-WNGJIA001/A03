# Makefile for Assignment 3 CSC3022F 2021
# Author: WNGJIA001

# Macros definition
CC = g++
BIN_DIR = ./bin/
SRC_DIR = ./src/
BUILD_DIR = ./build/
TEST_DIR = ./tests/
CFLAGS = -c -Wall -Iinclude
rm = rm -f

# target and objects declaration
TARGET = $(BUILD_DIR)findcomp
OBJECTS = $(BIN_DIR)cmdlineParser.o $(BIN_DIR)ConnectedComponent.o $(BIN_DIR)PGMimageProcessor.o $(BIN_DIR)driver.o

# link object files to create executable file extractor
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ -std=c++2a
# compile source files to create object files
$(BIN_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

.PHONY: test clean

TEST_TARGET = $(BUILD_DIR)testsuite
TEST_OBJECTS = $(BIN_DIR)test_ConnectedComponent.o $(BIN_DIR)ConnectedComponent.o $(BIN_DIR)test_PGMimageProcessor.o $(BIN_DIR)PGMimageProcessor.o $(BIN_DIR)test_main.o

test: $(TEST_TARGET)
	@$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $^ -o $@ -std=c++2a

$(BIN_DIR)test_main.o: $(TEST_DIR)test_main.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

$(BIN_DIR)test_ConnectedComponent.o: $(TEST_DIR)test_ConnectedComponent.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

$(BIN_DIR)ConnectedComponent.o: $(SRC_DIR)ConnectedComponent.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

$(BIN_DIR)test_PGMimageProcessor.o: $(TEST_DIR)test_PGMimageProcessor.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

$(BIN_DIR)PGMimageProcessor.o: $(SRC_DIR)PGMimageProcessor.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

# remove all the object binary files and executable file
clean:
	$(rm) $(BIN_DIR)*.o $(BIN_DIR)*.pgm
	$(rm) $(BUILD_DIR)findcomp $(BUILD_DIR)testsuite