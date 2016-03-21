#include "stdafx.h"
#include "DataStruct.h"


DataStruct::DataStruct()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	motor1moving = false;
	motor2moving = false;
	motor3moving = false;
	gripperOpen = true;
	motor1change = 0;
	motor2change = 0;
	motor3change = 0;
	target1 = 0;
	target2 = 0;
	target3 = 0;
	inuse = false;
}

void DataStruct::setSensor(int x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	forceSensorInput = x;
	inuse = false;
}

int DataStruct::getSensor()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	//inuse = true;
	return forceSensorInput;
}

void DataStruct::setValues()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor1moving = false;
	motor2moving = false;
	motor3moving = false;
	gripperOpen = true;
	motor1change = 0;
	motor2change = 0;
	motor3change = 0;
	inuse = false;
	return;
}

void DataStruct::setValues(DataStruct * replacement)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor1moving = replacement->motor1moving;
	motor2moving = replacement->motor2moving;
	motor3moving = replacement->motor3moving;
	gripperOpen = replacement->gripperOpen;
	motor1change = replacement->motor1change;
	motor2change = replacement->motor2change;
	motor3change = replacement->motor3change;
	inuse = false;
	return;
}

bool DataStruct::getm1m()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return motor1moving;
}

bool DataStruct::getm2m()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return motor2moving;
}
bool DataStruct::getm3m()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return motor3moving;
}
float DataStruct::getm1c()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return motor1change;
}
float DataStruct::getm2c()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return motor2change;
}

float DataStruct::getm3c()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return motor3change;
}

bool DataStruct::getgo()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return gripperOpen;
}

void DataStruct::setm1m(bool x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor1moving = x;
	inuse = false;
}

void DataStruct::setm2m(bool x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor2moving = x;
	inuse = false;
}
void DataStruct::setm3m(bool x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor3moving = x;
	inuse = false;
}
void DataStruct::setm1c(float x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor1change = x;
	inuse = false;
}
void DataStruct::setm2c(float x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor2change = x;
	inuse = false;
}

void DataStruct::setm3c(float x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor3change = x;
	inuse = false;
}
void DataStruct::upm1c(float x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor1change += x;
	inuse = false;
	
}
void DataStruct::upm2c(float x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor2change += x;
	inuse = false;
}

void DataStruct::upm3c(float x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	motor3change += x;
	inuse = false;
}

void DataStruct::setgo(bool x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	gripperOpen = x;
	inuse = false;
}

float DataStruct::getandclearm1()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	float temp = motor1change;
	motor1change = 0;
	inuse = false;
	return temp;
}

float DataStruct::getandclearm2()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	float temp = motor2change;
	motor2change = 0;
	inuse = false;
	return temp;
}
float DataStruct::getandclearm3()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	float temp = motor3change;
	motor3change = 0;
	inuse = false;
	return temp;
}

int DataStruct::gett1()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return target1;
}

int DataStruct::gett2()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return target2;
}

int DataStruct::gett3()
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	return target3;
}

void DataStruct::sett1(int x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	target1 = x;
	inuse = false;
}

void DataStruct::sett2(int x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	target2 = x;
	inuse = false;
}

void DataStruct::sett3(int x)
{
	lockRef^ m_lock = gcnew lockRef();
	msclr::lock l(m_lock);
	while (inuse)
	{
	}
	inuse = true;
	target3 = x;
	inuse = false;
}