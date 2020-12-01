CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c -I/usr/local/include/
LDFLAGS=-Wall `pkg-config --libs opencv` -std=c++11 -lpigpio -lrt -lpthread -lraspicam -lraspicam_cv 

CC=g++

all: go

go: Main.o CCar.o CMotor.o CTrack.o CSonar.o
	$(CC) $(LDFLAGS) Main.o CCar.o CMotor.o CTrack.o CSonar.o -o go
	
Main.o: Main.cpp
	$(CC) $(CFLAGS) Main.cpp

CCar.o: CCar.cpp
	$(CC) $(CFLAGS) CCar.cpp
	
CMotor.o: CMotor.cpp
	$(CC) $(CFLAGS) CMotor.cpp

CTrack.o: CTrack.cpp
	$(CC) $(CFLAGS) CTrack.cpp
	
CSonar.o: CSonar.cpp
	$(CC) $(CFLAGS) CSonar.cpp
 
clean:
	rm *o
