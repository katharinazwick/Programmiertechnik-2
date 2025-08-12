_CXX_CLANG := $(shell command -v clang++ 2>/dev/null)
_CXX_GCC := $(shell command -v g++ 2>/dev/null)

ifeq ($(_CXX_CLANG),)
    ifeq ($(_CXX_GCC),)
        $(error "Neither clang++ nor g++ found in PATH. Please install one.")
    else
        COMPILER = g++
    endif
else
    COMPILER = clang++
endif

OPTIONS = -std=c++17
TEST_OPTIONS = -std=c++17 -Idoctest/doctest -Wall -pedantic -g
BUILD=../out
TESTS=../tests

EXE_SUFFIX =
ifeq ($(findstring MINGW,$(shell uname -s)),MINGW)
    EXE_SUFFIX = .exe
endif

COMPILE = $(COMPILER) $(OPTIONS)
TEST_COMPILE = $(COMPILER) $(TEST_OPTIONS)
EXECUTABLE = $(BUILD)/main$(EXE_SUFFIX)
TEST_EXECUTABLE = $(BUILD)/tests$(EXE_SUFFIX)
VLIB=$(wildcard ../src/vlib/*.cpp)
RM = rm -f 

SRC_DIR=../src
OBJ_DIR=$(BUILD)/obj

SOURCES = $(SRC_DIR)/main.cpp
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
all: tests routing

routing: prep
	$(COMPILE) $(VLIB) -o $(BUILD)/routing$(EXE_SUFFIX) $(SRC_DIR)/routing_cli.cpp
ifeq ($(EXE_SUFFIX),)
	chmod +x $(BUILD)/routing
endif

tests: prep $(TESTS)/tests.cpp
	$(TEST_COMPILE) $(TESTS)/tests.cpp $(VLIB) -o $(TEST_EXECUTABLE)
ifeq ($(EXE_SUFFIX),)
	chmod +x $(TEST_EXECUTABLE)
endif
	$(TEST_EXECUTABLE)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

prep:
	mkdir -p $(BUILD)

.PHONY: clean prep all main tests
clean:
	rm -rf $(BUILD)
