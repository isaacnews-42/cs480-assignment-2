CXX = g++
CXXFLAGS = -Wall -g

xsh: main.cpp xsh.h
	$(CXX) $(CXXFLAGS) -o xsh main.cpp

clean:
	rm -f xsh