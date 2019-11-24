#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"

using namespace okapi;
using namespace pros;

void chassis_control() {
	int left_power = master.get_analog(ANALOG_LEFT_Y);
	int right_power = master.get_analog(ANALOG_RIGHT_Y);
	chassis_tank_drive(right_power, -left_power);
}

void intake_control() {
	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
		intake_drive(200,200);
	} else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
		intake_drive(-100,-100);
	} else {
		intake_drive(0,0);
	}
}

void lever_control() {
	if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		lever_drive(-200);
		intake_drive(69, 69);
	} else if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		lever_drive(200);
		intake_drive(-42, -42);
	} else {
		lever_drive(0);
	}
}


void arm_control() {
	int armTarget = 0;
	int armIterate = 0;
	
	if (master.get_digital_new_press(DIGITAL_RIGHT)) {
		arm_drive(3);
	} else if (master.get_digital_new_press(DIGITAL_UP)) {
		arm_drive(4);
	} else if (master.get_digital_new_press(DIGITAL_LEFT)) {
		arm_drive(1);
	} else if(master.get_digital_new_press(DIGITAL_DOWN)) {
		arm_drive(2);
	} else if (master.get_digital_new_press(DIGITAL_Y)) {
		armIterate = 0;
		arm_motor.move_absolute(20, 200);
	}
}