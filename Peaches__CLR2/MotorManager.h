#pragma once

using namespace System;
using namespace System::IO::Ports;

static const char * motor1port = "COM4";
static const char * motor2port = "COM5";
static const char * motor3port = "COM6";
static const char * pumpport = "COM3";
static const bool m1connected = true;
static const bool m2connected = false;
static const bool m3connected = false;
static const bool p1connected = true;
//The purpose of this class is to recieve data input which represents the 

//give output
// assumptions: angle is given in relative coordinates form
class MotorManager {
public:
	void set_current_count(int encoder_count);
	void update_current(int change) { current_count += change; };
	bool Keep_Running(int input_angle);
	void set_target_value(float input_angle, int set_direction);
	int get_move_count() { return target_value - current_count; };
	bool get_direction();
	MotorManager(int start_count);
private:
	int current_count;
	int target_value;
	int maxCount;
	int minCount;
	
	//1 = forward -1 = backwards 
	int direction;
};

//should be called by creating
//MotorManager1, MotorManager2, MotorManager3