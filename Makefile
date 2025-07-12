# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g
INCLUDES = -Isrc -Ispec/lib -Ispec/lib/catch2

SRC_DIR = src
SPEC_DIR = spec
BUILD_DIR = build

SPEC_SOURCES = $(wildcard $(SPEC_DIR)/*_spec.cpp)
SPEC_OBJECTS = $(patsubst $(SPEC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SPEC_SOURCES))
SPEC_MAIN = $(BUILD_DIR)/main.o
TEST_RUNNER = $(BUILD_DIR)/run_tests

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

.PHONY: all
all: test

.PHONY: test
test: $(TEST_RUNNER)
	@echo "Running tests..."
	@./$(TEST_RUNNER)

$(TEST_RUNNER): $(SPEC_MAIN) $(SPEC_OBJECTS) $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: $(SPEC_DIR)/main.cpp $(SPEC_DIR)/lib/catch2/catch.hpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%_spec.o: $(SPEC_DIR)/%_spec.cpp $(SPEC_DIR)/lib/bdd.hpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: watch
watch:
	@echo "Watching for changes. Press Ctrl+C to stop."
	@while true; do \
		clear; \
		make test --no-print-directory; \
		fswatch -1 -r src spec --exclude build || true; \
	done

.PHONY: watch-entr
watch-entr:
	@find src spec -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | \
		entr -c make test

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: deps
deps: $(SPEC_DIR)/lib/catch2/catch.hpp $(SPEC_DIR)/lib/bdd.hpp

$(SPEC_DIR)/lib/catch2/catch.hpp:
	@echo "Downloading Catch2..."
	@mkdir -p $(SPEC_DIR)/lib/catch2
	@curl -sL https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp -o $@

$(SPEC_DIR)/lib/bdd.hpp:
	@echo "Downloading BDD helpers..."
	@mkdir -p $(SPEC_DIR)/lib
	@curl -sL https://raw.githubusercontent.com/s-ajensen/c2_bdd/refs/heads/master/c2_bdd.hpp -o $@

.PHONY: check
check:
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -fsyntax-only $(SPEC_DIR)/*_spec.cpp

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make test       - Build and run tests (default)"
	@echo "  make watch      - Auto-run tests on file changes (fswatch)"
	@echo "  make watch-entr - Auto-run tests on file changes (entr)"
	@echo "  make check      - Quick syntax check"
	@echo "  make deps       - Download test dependencies"
	@echo "  make clean      - Remove build artifacts"