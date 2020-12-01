CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c -I/usr/local/include/
LDFLAGS=-Wall `pkg-config --libs opencv` -std=c++11 -lpigpio -lrt -lpthread -lraspicam -lraspicam_cv 

CC=g++

all: manual

manual: Main.o CCar.o CMotor.o
	$(CC) $(LDFLAGS) Main.o CCar.o CMotor.o -o manual
	
Main.o: Main.cpp
	$(CC) $(CFLAGS) Main.cpp

CCar.o: CCar.cpp
	$(CC) $(CFLAGS) CCar.cpp
	
CMotor.o: CMotor.cpp
	$(CC) $(CFLAGS) CMotor.cpp
 
clean:
	rm *o
