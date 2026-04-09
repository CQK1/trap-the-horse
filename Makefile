# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -O2 -Iinclude

# Directories
SRC_DIR   := src
BUILD_DIR := build

# Targets
TARGET := d1 d2 d3

# Common object files from src/ (excluding drivers)
OBJS := $(BUILD_DIR)/Map.o $(BUILD_DIR)/Dijkstra.o

# Default rule
all: $(TARGET)

d1: $(OBJS) $(BUILD_DIR)/driver1.o
d2: $(OBJS) $(BUILD_DIR)/driver2.o
d3: $(OBJS) $(BUILD_DIR)/driver3.o

# Link step
$(TARGET):
	$(CXX) $^ -o $@

# Compile step
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean