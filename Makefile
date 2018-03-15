CXX = g++
CXXFLAGS = -Wall -std=c++11 -O3 

Project2: main.cpp dList.cpp
	$(CXX) $(CXXFLAGS)  main.cpp dList.cpp -o Project2
