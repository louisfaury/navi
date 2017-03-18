#Serial  makefile  

.SUFFIXES :  
.PHONY : clean


CXX = g++
C = gcc
CXXFLAGS = -std=c++11 -w 
CFLAGS = -w
OBJ = Serial.o


all : $(OBJ)


%.o : %.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)


clean : 
	rm -rf *.o 



