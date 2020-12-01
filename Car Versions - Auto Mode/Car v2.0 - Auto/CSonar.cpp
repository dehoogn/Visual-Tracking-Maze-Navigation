// CSonar.cpp
// Ultrasonic Range Finder Control Class

// Echo returns a 5v signal which can damage the pi
// Use a voltage divider to return 3.3v
// Resistances of 4.7k and 10k will work
// Vcc = +5v
// Trigger = GPIO23 - Pin 16
// Echo = GPIO24 - Pin 18
// GND = Ground

#include "CSonar.h"
#include <unistd.h>
#include "pigpio.h"

#define HIGH 1
#define LOW 2

// CSonar Constructor
CSonar::CSonar()
{
	gpioInitialise();
	distance = 0;
	
	gpioSetMode(Trig, PI_OUTPUT);
	gpioSetMode(Echo, PI_INPUT);
	
	gpioWrite(Trig, LOW);
	gpioDelay(50);
}

// Gets the distance from range finder
void CSonar::Distance(void)
{
	gpioTrigger(Trig, 20, HIGH);
	
	while(gpioRead(Echo) == 0);
	long start = gpioTick();
	
	while(gpioRead(Echo) == 1);
	long end = gpioTick();
	
	long final = end - start;
	distance = (final/58);
	
}


// CSonar Destructor
CSonar::~CSonar()
{
	gpioTerminate();
}
