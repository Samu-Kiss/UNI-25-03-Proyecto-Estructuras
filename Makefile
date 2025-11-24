# Makefile para el proyecto de estructuras
# Uso:
#  make                -> compila en release y genera `programa.exe`
#  make debug          -> compila con símbolos de depuración
#  make clean          -> borra `build/` y el ejecutable
#  make run            -> ejecuta `./programa.exe`

CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -MMD -MP
LDFLAGS ?=

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp, build/%.o, $(SOURCES))
DEPS := $(OBJECTS:.o=.d)

TARGET := programa.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

-include $(DEPS)

clean:
	rm -rf build $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -g -O0
debug: clean all

rebuild: clean all

.PHONY: all clean run debug rebuild

help:
	@echo "Targets disponibles: all, debug, clean, rebuild, run"
	@echo "Para usar otro compilador: make CXX=path/to/g++"
