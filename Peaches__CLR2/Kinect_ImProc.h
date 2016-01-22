#include <Windows.h>
#include <Ole2.h>

#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>

#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <fstream>
#include <string>

//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui.hpp"

#include "ThreeDPos.h"

#define width 640
#define height 480

class Kinect_ImProc
{
public:
	Kinect_ImProc(bool debug);
	Kinect_ImProc();
	bool initKinect();
	void getRgbData(GLubyte* dest);
	void getDepthData(GLubyte* dest);
	void getKinectData();
	void setCounter(int count);
	void debug_print();
	bool checkImage();
	double estimatePixelSize(long distance);
	int checkPixel(float red, float green, float blue);
	int getCenterOfPeach();
	ThreeDPos *position;
	void setPositionValues(int pix);
private:
	HANDLE rgbStream;
	HANDLE depthStream;
	INuiSensor* sensor;

	bool debug_mode;
	bool print;
	int counter;

	long depthToRgbMap[width * height * 2];
	float colorarray[width * height * 3];
	float vertexarray[width * height];
	int locationpeaches[width * height];
	double redmin;
	double redmax;
	double greenmin;
	double greenmax;
	double bluemin;
	double bluemax;
};
