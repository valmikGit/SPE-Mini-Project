# Makefile (no CMake)
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
TEST_DIR := tests

APP := $(BIN_DIR)/calculator
TEST_BIN := $(BIN_DIR)/tests

DOCKER_IMAGE ?= scientific-calculator
DOCKER_USER ?=
IMAGE_TAG ?= latest
DOCKER_FULL ?= $(DOCKER_USER)/$(DOCKER_IMAGE):$(IMAGE_TAG)

SRC := $(SRC_DIR)/main.cpp $(SRC_DIR)/calculator.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

TEST_SRC := $(TEST_DIR)/test_runner.cpp $(SRC_DIR)/calculator.cpp
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/tests_%.o, $(TEST_SRC))

.PHONY: all build test clean docker-build docker-push docker-run

all: build

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/calculator.o: $(SRC_DIR)/calculator.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(APP): $(BIN_DIR) $(BUILD_DIR)/calculator.o $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build: $(APP)

# Tests build
$(BUILD_DIR)/tests_test_runner.o: $(TEST_DIR)/test_runner.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BUILD_DIR)/tests_calculator.o: $(SRC_DIR)/calculator.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(TEST_BIN): $(BIN_DIR) $(BUILD_DIR)/tests_test_runner.o $(BUILD_DIR)/tests_calculator.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

# Docker
docker-build:
	@if [ -z "$(DOCKER_USER)" ]; then \
	  echo "Warning: DOCKER_USER not set. Building image without namespace."; \
	  docker build -t $(DOCKER_IMAGE):$(IMAGE_TAG) . ; \
	else \
	  docker build -t $(DOCKER_FULL) . ; \
	fi

docker-push:
	@if [ -z "$(DOCKER_USER)" ]; then \
	  echo "Please set DOCKER_USER to push to Docker Hub." ; exit 1; \
	else \
	  docker push $(DOCKER_FULL) ; \
	fi

docker-run:
	# run interactive container exposing port 8080 (if app listens); for our terminal app just starts shell
	@if [ -z "$(DOCKER_USER)" ]; then \
	  docker run --rm -it $(DOCKER_IMAGE):$(IMAGE_TAG) ; \
	else \
	  docker run --rm -it $(DOCKER_FULL) ; \
	fi

.PHONY: lint