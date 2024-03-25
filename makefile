# Maintainer: benson
# Last update: 2024-03-20

# Compile C++17 code with clang++
CXX=clang++

# Compile flags
CXXFLAGS=-std=c++17 -Wall -Wextra

# Link flags
LDFLAGS=-lstdc++

# Target file
TARGET=judge.exe

# Source files
SOURCES=main.cpp \
		lib/*.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCES)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf ./generated-files ./results

run: $(TARGET)
	./$(TARGET)

.PHONY: clean