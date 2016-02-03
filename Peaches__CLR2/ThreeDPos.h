//#include "stdafx.h"

class ThreeDPos
{
public:
	ThreeDPos();
	double getX();
	double getY();
	double getZ();

	void setX(double in);
	void setY(double in);
	void setZ(double in);
private:
	double x;
	double y;
	double z;
};