#include <msclr\marshal_cppstd.h>
#include <msclr\lock.h>
class DataStruct
{
public:
	DataStruct();
	
	void setValues();
	void setValues(DataStruct * replacement);
	bool getm1m();
	bool getm2m();
	bool getm3m();
	float getm1c();
	float getm2c();
	float getm3c();
	bool getgo();
	float getandclearm1();
	float getandclearm2();
	float getandclearm3();

	void setm1m(bool x);
	void setm2m(bool x);
	void setm3m(bool x);
	void upm1c(float x);
	void upm2c(float x);
	void upm3c(float x);
	void setm1c(float x);
	void setm2c(float x);
	void setm3c(float x);
	void setgo(bool x);

private:
	bool motor1moving;
	bool motor2moving;
	bool motor3moving;
	bool gripperOpen;
	float motor1change;
	float motor2change;
	float motor3change;
	int motor1count;
	int motor2count;
	int motor3count;
};
