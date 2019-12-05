#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"

using namespace okapi;
using namespace pros;

void chassis_tank_drive(float left, float right) {
	chassis_right_rear.move(-right);
	chassis_right_front.move(-right);
	
	chassis_left_front.move(left);
	chassis_left_rear.move(left);

	// auto left_voltage = left / 127;
	// auto right_voltage = right / 127;
	// auto threshold = 10 / 127;
	// chassis.tank(left, right, threshold);
}

void intake_drive(float left_intake_speed, float right_intake_speed) {
	intake_motor_left.move(left_intake_speed);
	intake_motor_right.move(-right_intake_speed);
}

void lever_drive(float lever_speed) {
	lever_motor.move(lever_speed);
}

int armTarget = 0;
int armIterate = 0;

void arm_drive(int presetPos) {
	lever_drive(98);
	pros::delay(100);
	lever_drive(0);
	armIterate = presetPos;
	if (armIterate >= ARM_PRESETS_LEN) {
		armIterate = ARM_PRESETS_LEN;
	}
	armTarget = ARM_PRESETS[armIterate];
	master.print(0, 0, "Don't read this sentence %d", armTarget);
	arm_motor.move_absolute(armTarget, 200);
}