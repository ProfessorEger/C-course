CXX = clang++
CXXFLAGS = -c -D _DEBUG -ggdb3 -std=c++03 -Wall -Wextra -Weffc++ -Wcast-align -Wcast-qual -Wchar-subscripts -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -O0
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
TEST = test
TARGET = $(BIN_DIR)/bin
TARGET_TEST = $(BIN_DIR)/$(TEST)

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

TEST_SOURCES := $(wildcard $(SRC_DIR)/$(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(SRC_DIR)/$(TEST_DIR)/%.cpp,$(OBJ_DIR)/$(TEST_DIR)/%.o,$(TEST_SOURCES))

.PHONY: all test clean clean.o start

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

start: $(TARGET)
	cd $(BIN_DIR) && ./bin

test: $(TARGET_TEST)
	cd $(BIN_DIR) && ./$(TEST)

$(TARGET_TEST): $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS)) $(TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS)) $(TEST_OBJECTS) -o $(TARGET_TEST)

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(SRC_DIR)/$(TEST_DIR)/%.cpp | $(OBJ_DIR)/$(TEST_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/$(TEST_DIR):
	mkdir $(OBJ_DIR)/$(TEST_DIR)

$(BIN_DIR)/$(TEST_DIR):
	mkdir $(BIN_DIR)/$(TEST_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

clean.o:
	rm -rf $(OBJ_DIR)