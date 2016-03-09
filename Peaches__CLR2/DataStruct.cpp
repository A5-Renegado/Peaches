#include "stdafx.h"
#include "DataStruct.h"


DataStruct::DataStruct()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor1moving = false;
	motor2moving = false;
	motor3moving = false;
	gripperOpen = true;
	motor1change = 0;
	motor2change = 0;
	motor3change = 0;
}

void DataStruct::setValues()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor1moving = false;
	motor2moving = false;
	motor3moving = false;
	gripperOpen = true;
	motor1change = 0;
	motor2change = 0;
	motor3change = 0;
	return;
}

void DataStruct::setValues(DataStruct * replacement)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor1moving = replacement->motor1moving;
	motor2moving = replacement->motor2moving;
	motor3moving = replacement->motor3moving;
	gripperOpen = replacement->gripperOpen;
	motor1change = replacement->motor1change;
	motor2change = replacement->motor2change;
	motor3change = replacement->motor3change;
	return;
}

bool DataStruct::getm1m()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return motor1moving;
}

bool DataStruct::getm2m()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return motor2moving;
}
bool DataStruct::getm3m()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return motor3moving;
}
float DataStruct::getm1c()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return motor1change;
}
float DataStruct::getm2c()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return motor2change;
}

float DataStruct::getm3c()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return motor3change;
}

bool DataStruct::getgo()
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return gripperOpen;
}

void DataStruct::setm1m(bool x)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor1moving = x;
}

void DataStruct::setm2m(bool x)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor2moving = x;
}
void DataStruct::setm3m(bool x)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor3moving = x;
}
void DataStruct::setm1c(float x)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor1change = x;
}
void DataStruct::setm2c(float x)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor2change = x;
}

void DataStruct::setm3c(float x)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	motor3change = x;
}

void DataStruct::setgo(bool x)
{
	System::Object^ m_lock = gcnew System::Object();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	gripperOpen = x;
}