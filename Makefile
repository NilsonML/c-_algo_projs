# Сборка всех программ:  make        Тесты:  make test        Очистка:  make clean
# Нужен g++ (Linux/macOS/MinGW). Для MSVC см. README.

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -pedantic
BUILD    := build

SOURCES := $(filter-out misc/%,$(wildcard */*.cpp))
TARGETS := $(patsubst %.cpp,$(BUILD)/%,$(notdir $(SOURCES)))

vpath %.cpp sorting searching arrays math graphs parallel misc

.PHONY: all test clean ncurses
all: $(TARGETS)

$(BUILD)/openmp_sum: openmp_sum.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -fopenmp $< -o $@

$(BUILD)/%: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

# Отдельно: нужна библиотека ncurses (на Windows — PDCurses)
ncurses: misc/ncurses_calculator.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $(BUILD)/ncurses_calculator -lmenu -lncurses

$(BUILD):
	mkdir -p $(BUILD)

test: all
	./tests/run_tests.sh

clean:
	rm -rf $(BUILD)
