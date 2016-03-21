#pragma once
#include <stdlib.h>
using namespace System;
using namespace System::IO::Ports;

static const char * motor1port = "COM6";
static const char * motor2port = "COM4";
static const char * motor3port = "COM5";
static const char * pumpport = "COM3";
static const bool m1connected = false;
static const bool m2connected = true;
static const bool m3connected = true;
static const bool p1connected = false;
static const float theta1start = 0;
static const float theta2start = 90.0;
static const float theta3start = 180.0;
static const float theta1deposit = 0;
static const float theta2deposit = 0;
static const float theta3deposit = -90.0;

//The purpose of this class is to recieve data input which represents the 

//give output
// assumptions: angle is given in relative coordinates form
class MotorManager {
public:
	void set_current_count(int encoder_count);
	void update_current(int change) { current_count = change; };
	bool Keep_Running(int input_angle);
	void set_target_value(float input_angle, int set_direction);
	void set_target_rotation(float input_angle);
	int get_move_count() { return target_value - current_count; };
	int get_target() { return target_value; }
	bool get_direction();
	bool at_target() { return abs(target_value - current_count) < 50 || !inuse; };
	int get_current() { return current_count; }
	float get_current_angle();
	void apply_offset(float angle_change);
	void apply_absolute_offset(float abs_angle);
	void set_maxCount(int x) { maxCount = x; };
	void set_minCount(int x) { minCount = x; };
	void setcurrent_target() { current_count = target_value; }

	MotorManager(int start_count,bool use);
	MotorManager(int start_count, int aoffset_per_degree, float agear_ratio, bool use);
	MotorManager(int start_count, int aoffset_per_degree, bool use);
	MotorManager(int start_count, float agear_ratio, bool use);
private:
	int current_count;
	int target_value;
	int count_offset;
	int maxCount;
	int minCount;

	float gear_ratio;
	int offset_per_degree;

	bool inuse;
	
	//1 = forward -1 = backwards 
	int direction;
};