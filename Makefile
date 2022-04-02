CXX=g++
CXXFLAGS=-std=c++20 -pedantic -Wall
EXE=BTGPCPatcher

all: $(EXE)

$(EXE): BTGPCPatcher.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ -static

clean:
	rm -f $(EXE)
