#include "ThreeDPos.h"

ThreeDPos::ThreeDPos()
{
	x = 0;
	y = 0;
	z = 0;
}

double ThreeDPos::getX()
{
	return x;
}

double ThreeDPos::getY()
{
	return y;
}

double ThreeDPos::getZ()
{
	return z;
}

void ThreeDPos::setX(double in)
{
	x = in;
}

void ThreeDPos::setY(double in)
{
	y = in;
}

void ThreeDPos::setZ(double in)
{
	z = in;
}
