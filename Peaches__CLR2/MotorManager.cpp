#include "stdafx.h"
#include "MotorManager.h"

MotorManager::MotorManager(int start_count)
{
	current_count = start_count;
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
	target_value = (input_angle * 50);
	direction = set_direction;
}
