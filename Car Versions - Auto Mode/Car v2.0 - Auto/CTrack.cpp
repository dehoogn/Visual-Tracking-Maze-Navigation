#include "CTrack.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#define MIN_GREEN_AREA 50
#define MIN_ORANGE_AREA 200

using namespace cv;
using namespace std;

CTrack::CTrack()
{
	Camera.set(CV_CAP_PROP_FRAME_WIDTH,640);
	Camera.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	Camera.open();

	focallength = 0.210; //depends on the camera in use... 0.386 for 4618 cam, 0.337 for rpi cam
	heightobject = 1.9; //actual height of object
}
CTrack::~CTrack() { Camera.release();}

void CTrack::update()
{
	//read frame(image), store into Mat canvas
	Camera.grab();
	Camera.retrieve(canvas);

	cvtColor(canvas, HSV, COLOR_BGR2HSV); //convert colorspace of image, store into Mat7 HSV

	//Green:
	inRange(HSV, Scalar(40,150,70), Scalar(70,255,255), threshold1);
	//Orange:
	inRange(HSV, Scalar(0,150,110), Scalar(20,256,256), threshold2);
	inRange(HSV, Scalar(170,150,110), Scalar(180,256,256), threshold3);
	addWeighted(threshold2, 1, threshold3, 1, 0, threshold4);
	threshold2 = threshold4;
	
	//DILATION AND EROSION
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(4, 4));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(5, 5));


	erode(threshold1, threshold1, erodeElement);
	erode(threshold2, threshold2, erodeElement);

	dilate(threshold1, threshold1, dilateElement);
	dilate(threshold2, threshold2, dilateElement);

	erode(threshold1, threshold1, erodeElement);
	erode(threshold2, threshold2, erodeElement);

	//dilate(threshold1, threshold1, dilateElement);
	//dilate(threshold2, threshold2, dilateElement);
}

void CTrack::draw()
{
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	vector<Point> contour1;

	findContours(threshold1, contours1, hierarchy1, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (unsigned int i = 0; i < contours1.size(); i++)
	{
		Rect r = boundingRect(contours1.at(i));
		//filled contour:
		drawContours(threshold1, contours1, i, Scalar(255, 255, 255), -1, 8, hierarchy1);
		//outline contour:
		rectangle(canvas, r.tl(), r.br(), Scalar(0, 255, 0), 1, 8, 0);
		heightpixel1 = r.height;
		widthpixel1 = r.width;
		x1 = r.x + (r.width / 2);
	}

	vector<vector<Point>> contours2;
	vector<Vec4i> hierarchy2;
	vector<Point> contour2;

	findContours(threshold2, contours2, hierarchy2, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (unsigned int i = 0; i < contours2.size(); i++)
	{
		Rect r = boundingRect(contours2.at(i));

		drawContours(threshold2, contours2, i, Scalar(255, 255, 255), -1, 8, hierarchy2);
		rectangle(canvas, r.tl(), r.br(), Scalar(0, 255, 0), 1, 8, 0);
		heightpixel2 = r.height;
		widthpixel2 = r.width;
		x2 = r.x + (r.width / 2);
	}

	//use moments method to find our filtered object
	object1Found = false;
	object2Found = false;

	if (hierarchy1.size() > 0)
	{
		int numObjects = hierarchy1.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS)
		{
			if ((heightpixel1 * widthpixel1) > MIN_GREEN_AREA && (heightpixel1 * widthpixel1) < MAX_OBJECT_AREA)
			{
				object1Found = true;
				objectdistance = ((heightobject * focallength) / (heightpixel1 / 37.795275590551)) * 100;
			}
			else object1Found = false;
		}
	}

	if (hierarchy2.size() > 0)
	{
		int numObjects = hierarchy2.size();

		if (numObjects<MAX_NUM_OBJECTS)
		{
			if ((heightpixel2 * widthpixel2) > MIN_ORANGE_AREA && (heightpixel2 * widthpixel2) < MAX_OBJECT_AREA)
			{
				object2Found = true;
				objectdistance = ((heightobject * focallength) / (heightpixel2 / 37.795275590551)) * 100;
			}
			else object2Found = false;
		}
	}

	if (object1Found == true && object2Found == true)
	{
		colfound = "BOTH";
		objfound = 1;
	}
	else if (object1Found == true)
	{
		colfound = "GREEN";
		objfound = 2;
	}
	else if (object2Found == true)
	{
		colfound = "ORANGE";
		objfound = 3;
	}
	else if (object1Found == false && object2Found == false)
	{
		colfound = "NONE";
		objfound = 0;
	}
}

void CTrack::show()
{
	imshow("Threshold Orange", threshold2);
	imshow("Threshold Green", threshold1);
	imshow("Original Image", canvas);
	waitKey(5);
}

void CTrack::run()
{
	update();
	draw();
}
