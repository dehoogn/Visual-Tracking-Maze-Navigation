// CMotor.cpp
// Motor Control Class

/*
H-Bridge and Motor Pin Information
A01		Left Wheel 	GND
A02		Left Wheel 	Positve
BO1		Right Wheel Positive
B02		Right Wheel GND
VM		5V			Pin 2
VCC		3.3V		Pin 1
PWMA	GPIO 4		PIN 7
PWMB 	GPIO 11 	PIN 23
AIN1 	GPIO 27 	PIN 13
AIN2 	GPIO 17 	PIN 11
BIN1 	GPIO 10 	PIN 19
BIN2 	GPIO 9  	PIN 21
STBY 	GPIO 22 	PIN 15
*/

#include "CMotor.h"

// Motow PWM defines
#define POWERA 175 // Left Motor PWM (0-255 range)
#define POWERB 160 // Right Motor PWM (0-255 range)
#define FULLPOWER 255 // 100% Motor PWM

// GPIO defines
#define PWMA 4
#define PWMB 11
#define AIN1 27
#define AIN2 17
#define BIN1 10
#define BIN2 9
#define STBY 22


////////////////////////////////////
// CMotor Constructor
////////////////////////////////////
CMotor::CMotor()
{
	// Initialize the GPIO
	gpioInitialise();
	
	// Set Pin outputs
	gpioSetMode(PWMA, PI_OUTPUT);
	gpioSetMode(PWMB, PI_OUTPUT);
	gpioSetMode(AIN1, PI_OUTPUT);
	gpioSetMode(AIN2, PI_OUTPUT);
	gpioSetMode(BIN1, PI_OUTPUT);
	gpioSetMode(BIN2, PI_OUTPUT);
	gpioSetMode(STBY, PI_OUTPUT);
}


////////////////////////////////////
// CMotor Deconstructor
////////////////////////////////////
CMotor::~CMotor()
{
	// Terminate GPIO
	gpioTerminate();
}


////////////////////////////////////
// Stop the car
////////////////////////////////////
void CMotor::stop(void)
{
	gpioPWM(PWMA , POWERA);
	gpioWrite(AIN1 , 0);
   	gpioWrite(AIN2 , 0);
	gpioWrite(STBY , 0);
	
	gpioPWM(PWMB , POWERB);
	gpioWrite(BIN1 , 0);
   	gpioWrite(BIN2 , 0);
	gpioWrite(STBY , 0);
}


////////////////////////////////////
// Move the car forward
////////////////////////////////////
void CMotor::forward(void)
{
	gpioPWM(PWMA , POWERA);
	gpioWrite(AIN1 , 1);
   	gpioWrite(AIN2 , 0);
	gpioWrite(STBY , 1);
	
	gpioPWM(PWMB , POWERB);
	gpioWrite(BIN1 , 1);
   	gpioWrite(BIN2 , 0);
	gpioWrite(STBY , 1);
}


////////////////////////////////////
// Move the car backwards
////////////////////////////////////
void CMotor::back(void)
{
	gpioPWM(PWMA , POWERA);
	gpioWrite(AIN1 , 0);
   	gpioWrite(AIN2 , 1);
	gpioWrite(STBY , 1);
	
	gpioPWM(PWMB , POWERB);
	gpioWrite(BIN1 , 0);
   	gpioWrite(BIN2 , 1);
	gpioWrite(STBY , 1);
}


////////////////////////////////////
// Turn the car left
////////////////////////////////////
void CMotor::left (void)
{
	gpioPWM(PWMA , POWERA);
	gpioWrite(AIN1 , 0);
   	gpioWrite(AIN2 , 1);
	gpioWrite(STBY , 1);
	
	gpioPWM(PWMB , POWERB);
	gpioWrite(BIN1 , 1);
   	gpioWrite(BIN2 , 0);
	gpioWrite(STBY , 1);
}


////////////////////////////////////
// Turn the car right
////////////////////////////////////
void CMotor::right (void)
{
	gpioPWM(PWMA , POWERA);
	gpioWrite(AIN1 , 1);
   	gpioWrite(AIN2 , 0);
	gpioWrite(STBY , 1);
	
	gpioPWM(PWMB , POWERB);
	gpioWrite(BIN1 , 0);
   	gpioWrite(BIN2 , 1);
	gpioWrite(STBY , 1);
}
