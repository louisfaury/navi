#Com makefile  

.SUFFIXES :  
.PHONY : clean


CXX = g++
C = gcc
CXXFLAGS = -std=c++11 -w 
CFLAGS = -w
OBJ = Communication.o Message.o MessageChecker.o MessageSender.o PingProcessor.o MessageProcessor.o


all : $(OBJ)


%.o : %.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)


clean : 
	rm -rf *.o 



