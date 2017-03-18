#main Makefile 

.SUFFIXES :  
.PHONY : clean


prefix = $(shell pwd)
srcdir = $(prefix)/src
libdir = $(prefix)/lib/
bindir = $(prefix)/bin/
CXX = g++
C = gcc
CXXFLAGS = -std=c++11 -w 
CFLAGS = -w
OBJ = $(srcdir)/Thread/*.o $(srcdir)/Drone/*.o $(srcdir)/Autopilot/*.o $(srcdir)/Utils/*.o $(srcdir)/Com/*.o $(srcdir)/INS_EKF/*.o $(srcdir)/MaestroMotor/*.o $(srcdir)/Navi_Exception/*.o $(srcdir)/Serial/*.o 


all :
	make %.o
	$(CXX) $(OBJ) -o main $(CXXFLAGS)	
	@echo SUCCESS	

%.o :
	make -C src/Thread/ 
	make -C src/Drone/
	make -C src/Autopilot/
	make -C src/Com/ 
	make -C src/INS_EKF/
	make -C src/MaestroMotor/ 
	make -C src/Navi_Exception/
	make -C src/Serial/ 
	make -C src/Utils/ 



clean : 
	make -C src/Com/ clean 
	make -C src/Thread/ clean
	make -C src/Drone/ clean
	make -C src/Autopilot/ clean
	make -C src/INS_EKF/ clean
	make -C src/MaestroMotor/ clean
	make -C src/Navi_Exception/ clean 
	make -C src/Serial/ clean 
