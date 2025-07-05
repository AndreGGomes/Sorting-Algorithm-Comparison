CXX = g++
CXXFLAGS = -std=c++17

SRC = main.cpp
TARGET = main

all:
	$(CXX) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f tables/*.csv