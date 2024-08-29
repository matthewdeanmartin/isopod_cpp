# Path to cmake executable
CMAKE_PATH=/C/Program Files/JetBrains/CLion 2024.1.2/bin/cmake/win/x64/bin/cmake.exe

# Path to Ninja executable
NINJA_PATH=/C/Program Files/JetBrains/CLion 2024.1.2/bin/ninja/win/x64/ninja.exe

# Source directory
SRC_DIR=/C/github/isopod_cpp

# Build directory
BUILD_DIR=$(SRC_DIR)\cmake-build-debug

# Target name
TARGET=isopod_cpp

# Number of parallel jobs for build
JOBS=18

# Source files for format and lint
SRC_FILES=$(wildcard *.cpp) $(wildcard *.h)

# Default target
all: format lint build test

# Format the code using clang-format
format:
	@echo "Formatting code with clang-format..."
	clang-format -i $(SRC_FILES)

# Lint the code using clang-tidy
lint:
	@echo "Linting code with clang-tidy..."
	clang-tidy $(SRC_FILES) -- -std=c++17

# Configure and build the project using cmake and Ninja
build:
	@echo "Configuring and building the project..."
	"$(CMAKE_PATH)" -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_MAKE_PROGRAM=$(NINJA_PATH)" -G Ninja -S $(SRC_DIR) -B $(BUILD_DIR)
	"$(CMAKE_PATH)" --build $(BUILD_DIR) --target $(TARGET) -j $(JOBS)

# Run tests using ctest
test:
	@echo "Running tests..."
	"$(CMAKE_PATH)" --build $(BUILD_DIR) --target test

# Clean build directory
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)/*

# Phony targets to prevent conflicts with files named 'all', 'format', etc.
.PHONY: all format lint build test clean
