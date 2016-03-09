#include "stdafx.h"
#include "DataStruct.h"

DataStruct::DataStruct()
{
	motor1moving = false;
	motor2moving = false;
	motor3moving = false;
	motor1change = 0;
	motor2change = 0;
	motor3change = 0;
}

void DataStruct::setValues()
{
	motor1moving = false;
	motor2moving = false;
	motor3moving = false;
	motor1change = 0;
	motor2change = 0;
	motor3change = 0;
	return;
}