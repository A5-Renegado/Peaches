#include "stdafx.h"
#include "MotorManager.h"

MotorManager::MotorManager(int start_count)
{
	current_count = start_count;
	gear_ratio = 1;
	offset_per_degree = 0;
	target_value = 0;
}

MotorManager::MotorManager(int start_count, float agear_ratio)
{
	current_count = start_count;
	gear_ratio = agear_ratio;
	offset_per_degree = 0;
	target_value = 0;
}

MotorManager::MotorManager(int start_count, int aoffset_per_degree)
{
	current_count = start_count;
	gear_ratio = 1;
	offset_per_degree = aoffset_per_degree;
	target_value = 0;
}

MotorManager::MotorManager(int start_count, int aoffset_per_degree, float agear_ratio)
{
	current_count = start_count;
	gear_ratio = agear_ratio;
	offset_per_degree = aoffset_per_degree;
	target_value = 0;
}

bool MotorManager::get_direction()
{
	if (current_count > target_value)
	{
		return true;
	}
	return false;
}

void MotorManager::set_current_count(int encoder_count)
{
	current_count = encoder_count;
	if (current_count >= 18000)
	{
		current_count %= 18000;
	}
}

bool MotorManager::Keep_Running(int input_angle)
{
	if (input_angle*50 < target_value) {
		return true;
	}
	else
	{
		return false;
	}
	

}

void MotorManager::set_target_value(float input_angle, int set_direction)
{
	target_value = ((int)(input_angle * 50.0)-(count_offset))/gear_ratio;
	direction = set_direction;
}

void MotorManager::set_target_rotation(float input_angle)
{
	target_value = current_count + (int)((input_angle * 50.0)/gear_ratio);
}

float MotorManager::get_current_angle()
{
	return 50.0*(float)(current_count + count_offset);
}

void MotorManager::apply_offset(float angle_change)
{
	count_offset += angle_change * offset_per_degree;
}
