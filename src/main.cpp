#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"

using namespace okapi;
using namespace pros;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Hello Pros User!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void disabled() {}

void competition_initialize() {}

void chassis_tank_drive(float left, float right) {
	chassis_right_rear.move(right);
	chassis_right_front.move(right);
	
	chassis_left_front.move(-left);
	chassis_left_rear.move(-left);
}

void chassis_control() {
	int left_power = master.get_analog(ANALOG_LEFT_Y);
	int right_power = master.get_analog(ANALOG_RIGHT_Y);
	chassis_tank_drive(right_power, left_power);
}

void intake_drive(float left_intake_speed, float right_intake_speed) {
	intake_motor_left.move(left_intake_speed);
	intake_motor_right.move(-right_intake_speed);
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

void lever_drive(float lever_speed) {
	lever_motor.move(lever_speed);
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

void opcontrol() {
	while (true) {
		//chassis stuff
		chassis_control();

		//intake
		intake_control();

		//lever stuff
		lever_control();

		// lift from korvex 
		arm_control();
		pros::delay(20);
	}
}