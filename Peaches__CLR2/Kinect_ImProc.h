#include <Windows.h>
#include <Ole2.h>

#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <gl/glut.h>
#ifdef __cplusplus
}
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "ThreeDPos.h"
#include "DataStruct.h"
#include "MotorManager.h"

#define width 640
#define height 480
#define GL_BGRA 0x80E1

extern DataStruct * globalfVMS;// = new DataStruct();
extern MotorManager * MotorManager1;// = new MotorManager(0);
extern MotorManager * MotorManager2;// = new MotorManager(0);
extern MotorManager * MotorManager3;// = new MotorManager(0);
static const bool comms = true;

class Kinect_ImProc
{
public:
	Kinect_ImProc(bool debug);
	Kinect_ImProc();
	~Kinect_ImProc() {};
	bool initKinect();
	void getRgbData(GLubyte* dest, GLubyte* dest2);
	void getDepthData(GLubyte* dest);
	void getKinectData();
	void setCounter(int count);
	void debug_print();
	bool check_debug();
	bool checkImage();
	double estimatePixelSize(long distance);
	int checkPixel(float red, float green, float blue);
	int getCenterOfPeach();
	ThreeDPos *position;
	void setPositionValues(int pix);
	GLuint textureId;
	GLubyte data[width*height * 4];
	bool thereisapeach;
	ThreeDPos * getPosition();
private:
	HANDLE rgbStream;
	HANDLE depthStream;
	INuiSensor* sensor;

	bool lockPosition;
	bool comLockPosition;

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
/*#ifndef MotorManager1
MotorManager * MotorManager1;
#endif
#ifndef MotorManager2
MotorManager * MotorManager2;
#endif
#ifndef MotorManager3
MotorManager * MotorManager3;
#endif*/