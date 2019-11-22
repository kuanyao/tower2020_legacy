#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"

using namespace okapi;
using namespace pros;

void chassis_tank_drive(float left, float right) {
	chassis_right_rear.move(right);
	chassis_right_front.move(right);
	
	chassis_left_front.move(-left);
	chassis_left_rear.move(-left);
}

void intake_drive(float left_intake_speed, float right_intake_speed) {
	intake_motor_left.move(left_intake_speed);
	intake_motor_right.move(-right_intake_speed);
}

void lever_drive(float lever_speed) {
	lever_motor.move(lever_speed);
}