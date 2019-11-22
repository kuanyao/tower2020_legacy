#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"

using namespace okapi;
using namespace pros;

void chassis_control() {
	int left_power = master.get_analog(ANALOG_LEFT_Y);
	int right_power = master.get_analog(ANALOG_RIGHT_Y);
	chassis_tank_drive(right_power, left_power);
}

void intake_control() {
	if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
		intake_drive(127,127);
	} else if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
		intake_drive(-100,-100);
	} else {
		intake_drive(0,0);
	}
}

void lever_control() {
	if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		lever_drive(-127);
		intake_drive(-40, -40);
	} else if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		lever_drive(127);
		intake_drive(40, 40);
	} else {
		lever_drive(0);
	}
}

int armTarget = 0;
int armIterate = 0;
void arm_control() {
	if (master.get_digital_new_press(DIGITAL_RIGHT)) {
		lever_drive(80);
		pros::delay(100);
		lever_drive(0);
		armIterate++;
		if (armIterate >= ARM_PRESETS_LEN) {
			armIterate = ARM_PRESETS_LEN;
		}
		armTarget = ARM_PRESETS[armIterate];
		master.print(0, 0, "Hello Pranav %d", armTarget);
		arm_motor.move_absolute(armTarget, 200);
	} else if (master.get_digital_new_press(DIGITAL_Y)) {
		armIterate = 0;
		lever_drive(-125);
		pros::delay(200);
		lever_drive(0);
		arm_motor.move_absolute(20, 200);
	}
}