CXX = g++
CXXFLAGS = -Wall -g

xsh: main.cpp xsh.h
	$(CXX) $(CXXFLAGS) -o xsh main.cpp executor.cpp parzer.cpp

clean:
	rm -f xsh