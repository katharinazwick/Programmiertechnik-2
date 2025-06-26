COMPILER = clang++
OPTIONS = -std=c++17
TEST_OPTIONS = -std=c++17 -Idoctest/doctest -Wall -pedantic -g
BUILD=../out
TESTS=../tests

COMPILE= $(COMPILER) $(OPTIONS)
TEST_COMPILE= $(COMPILER) $(TEST_OPTIONS)

SRC_DIR=../src
OBJ_DIR=$(BUILD)/obj
 
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/grading_table.cpp $(SRC_DIR)/grading_tasks.cpp
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: main ../tests

main: $(OBJECTS)
 	$(COMPILER) -o $(BUILD)/main $(OBJECTS)
 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
 	mkdir -p $(OBJ_DIR)
 	$(COMPILE) -c $< -o $@

tests: prep
	$(TEST_COMPILE) $(TESTS)/tests.cpp -o $(BUILD)/tests
	chmod +x $(BUILD)/tests
	$(BUILD)/tests

.PHONY: clean prep
clean: 
	rm -rf $(BUILD)
prep: 
	mkdir -p $(BUILD) $(OBJ_DIR)
