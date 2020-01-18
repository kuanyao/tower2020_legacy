#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"

using namespace okapi;
using namespace pros;
//chassis
void chassis_tank_drive(int left, int right) {
    const double chassis_movement_threshold = 0.05;
    chassis.tank(left / 127.0, right / 127.0, chassis_movement_threshold);
}
//intake
void intake_drive(float left_intake_speed, float right_intake_speed) {
	intake_motor_left.move(left_intake_speed);
	intake_motor_right.move(-right_intake_speed);
}
//lever
void lever_drive(float lever_speed) {
	lever_motor.move(lever_speed);
}

int armTarget = 0;
int armIterate = 0;

void arm_drive(int presetPos) {
	//so arm doesn't click w/ gear
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