#pragma once
#include <string>
#include "pigpio.h"
#include <opencv2/opencv.hpp>
#include "raspicam_cv.h"

//#define WIN
#define RPI

#include <string>

#ifdef WIN
#include "opencv.hpp"
#endif

#ifdef RPI
#include "pigpio.h"
#include <opencv2/opencv.hpp>
#endif

using namespace cv;
using namespace std;

class CTrack
{
private:
	int deviceid; //default is 0, any additional webcam connection is 1+
	VideoCapture capture; //videocapture object
	raspicam::RaspiCam_Cv Camera;
	Mat HSV; // stores colorspace-converted image
	Mat threshold1; //stores binary threshold-filtered image
	Mat threshold2;
	Mat threshold3;
	Mat threshold4;
	
	//for if GREEN, ORANGE, or BLUE found on the screen
	bool object1Found = false;
	bool object2Found = false;

	//for calculating distance from camera (in centimeters)
	int heightpixel1; //height of object as appeared on-screen(in pixels)
	int widthpixel1;
	int heightpixel2; //height of object as appeared on-screen(in pixels)
	int widthpixel2;
	double focallength; //depends on the camera in use
	double heightobject; //actual height of object

	//default capture width and height
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS = 3;
	//minimum and maximum object area
	const int MIN_OBJECT_AREA = 40 * 40;
	const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1;

public:
	CTrack(); //constructor
	~CTrack();

	int x1 = 0; //x value for location of the object (GREEN)
	int x2 = 0; //x value for ORANGE
	
	int objfound = 0;
	string colfound = "GREEN";
	double objectdistance;

	void update();
	void draw();
	void run();
	void show();

	cv::Mat canvas;
};

