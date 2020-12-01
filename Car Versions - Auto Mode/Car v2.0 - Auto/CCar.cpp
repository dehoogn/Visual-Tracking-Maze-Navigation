// CCar.cpp
// Car Control Class

#include "CCar.h"

//Sleep Times
#define LONG_RUN_TIME 600000
#define RUN_TIME 300000
#define SHORT_RUN_TIME 100000
#define ADJUST_TIME 15000
#define SHORT_ADJUST_TIME 11500
#define LEFT_TIME 350000
#define RIGHT_TIME 310000

//Values that bound the car adjustments
//as they attempt to centre the colour
//objects in the centre of the screen
#define X_MIN_LONG 280
#define X_MAX_LONG 360
#define X_MIN_SHORT 300
#define X_MAX_SHORT 340

////////////////////////////////////
// CCar Constructor
////////////////////////////////////
CCar::CCar()
{}


////////////////////////////////////
// Runs the car
// Monitors for key presses in manual mode
// Calls the guidance class in autonomous mode
////////////////////////////////////
void CCar::run(void)
{
	int dist = 0;
	int found = 0;
	//motor_test();
	//image_test();
	//sonar_test();
	
	while(1)
	{
		// Range Finding
		sonar.Distance();
		dist = sonar.distance;
		cout << "Distance: " << sonar.distance << "   ";
		
		// Colour Tracking
		guidance.run();
		found = guidance.objfound;
		cout << "Colour: " << guidance.colfound << endl;
		
		//Very Long Distance Logic
		if ((dist > 25) && (found != 0))
		{
			adjust(ADJUST_TIME, X_MIN_LONG, X_MAX_LONG);
			motion(LONG_RUN_TIME);
		}
		
		// Long Driving Distance Logic
		if ((dist < 25) && (dist > 10) && (found != 0))
		{
			adjust(ADJUST_TIME, X_MIN_LONG, X_MAX_LONG);
			motion(RUN_TIME);
		}
		
		// Short Driving Distance Logic
		if ((dist < 10) && (dist > 5) && (found != 0))
		{
			adjust(SHORT_ADJUST_TIME, X_MIN_SHORT, X_MAX_SHORT);
			motion(SHORT_RUN_TIME);
		}
		
		// Turning Distance Logic
		if ((dist < 5) && (found != 0))
		{
			if (guidance.colfound == "GREEN")
				right();
				
			if (guidance.colfound == "ORANGE")
				left();
			
			if (guidance.colfound == "BOTH")
				motor.stop();
		}
		
		// Stop Mode If No Object Found
		// And show image
		if (found == 0)
		{
			motor.stop();
			//guidance.show();
		}
	}
	
}


////////////////////////////////////
// Centres the car along the X-axis
////////////////////////////////////
void CCar::adjust(int t, int x_min, int x_max)
{
	//Adjustments for green marker or both
	if ((guidance.colfound == "GREEN") || (guidance.colfound == "BOTH"))
	{
		do 
		{
			guidance.run();
			
			//Left adjust
			if (guidance.x1 > x_max)
			{
				motor.left();
				usleep(t);
				motor.stop(); 
			}
			
			//Right adjust
			if (guidance.x1 < x_min)
			{
				motor.right();
				usleep(t);
				motor.stop(); 
			}
		} while ((guidance.x1 < x_min) || (guidance.x1 > x_max));
	}
	
	//Adjustments for orange marker
	if (guidance.colfound == "ORANGE")
	{
		do 
		{
			guidance.run();
			
			//Left adjust
			if (guidance.x2 > x_max)
			{
				motor.left();
				usleep(t);
				motor.stop(); 
			}
			
			//Right adjust
			if (guidance.x2 < x_min)
			{
				motor.right();
				usleep(t);
				motor.stop(); 
			}
		} while ((guidance.x2 < x_min) || (guidance.x2 > x_max));
	}
	
}


////////////////////////////////////
// Moves the car forward a set distance
////////////////////////////////////
void CCar::motion(int t)
{
	// Distance check
	if ((sonar.distance > 5) && (sonar.distance <150))
	{
		motor.forward();
		usleep(t);
		motor.stop();
	}
}


////////////////////////////////////
// Left Turn
////////////////////////////////////
void CCar::left(void)
{
	motor.left();
	usleep(LEFT_TIME);
	motor.stop();
}


////////////////////////////////////
// Right Turn
////////////////////////////////////
void CCar::right(void)
{
	motor.right();
	usleep(RIGHT_TIME);
	motor.stop();
}


////////////////////////////////////
// Motor Control Test
////////////////////////////////////
void CCar::motor_test(void)
{
	motor.forward();
	sleep(2);
	motor.stop();
	sleep(2);
	motor.back();
	sleep(2);
	motor.stop();
	sleep(2);
	motor.left();
	usleep(LEFT_TIME);
	motor.stop();
	sleep(2);
	motor.right();
	usleep(RIGHT_TIME);
	motor.stop();
}


////////////////////////////////////
// Guidance Camera Test
////////////////////////////////////
void CCar::image_test(void)
{
	while(1)
	{
		guidance.run();
		guidance.show();
		cout << "Colour: " << guidance.colfound << endl;
	}
}


////////////////////////////////////
// Ultrasonic Rangefinder Test
////////////////////////////////////
void CCar::sonar_test(void)
{
	while(1)
	{
		sonar.Distance();
		cout << "Distance: " << sonar.distance << endl;
		sleep(1);
	}
}
