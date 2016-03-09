#include <msclr\marshal_cppstd.h>
#include <msclr\lock.h>
class DataStruct
{
public:
	DataStruct();
	bool motor1moving;
	bool motor2moving;
	bool motor3moving;
	bool gripperOpen;
	float motor1change;
	float motor2change;
	float motor3change;
	void setValues();
	void setValues(DataStruct * replacement);
	bool getm1m();
	bool getm2m();
	bool getm3m();
	float getm1c();
	float getm2c();
	float getm3c();
	bool getgo();

	void setm1m(bool x);
	void setm2m(bool x);
	void setm3m(bool x);
	void setm1c(float x);
	void setm2c(float x);
	void setm3c(float x);
	void setgo(bool x);

};
