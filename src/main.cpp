#include "main.h"
#include "okapi/api.hpp"

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
		pros::lcd::set_text(2, "look behind you");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello");

	pros::lcd::register_btn1_cb(on_center_button);
}

	void disabled() {}

	void competition_initialize() {}

	void autonomous() {}

void opcontrol() {
 	pros::Motor intake_motor(5); 
	pros::Motor intake_motor2(2);
	pros::Motor lever_motor(19);
	pros::Motor chassis_right_bottom(1);
	pros::Motor chassis_right_top(11);
	pros::Motor chassis_left_bottom(10);
	pros::Motor chassis_left_top(20);
	pros::Motor arm_motor(18);
	pros::Controller master (E_CONTROLLER_MASTER);

	const int ARM_PRESETS[4]  = {0, -1020, -1405, -2050};
	const int ARM_PRESETS_LEN = 3;
	int armTarget = 0;
	int armIterate = 0;

	// void chassis_move_relative(float distance) {
	// 	chassis_right_bottom.move_relative(distance);
	// 	chassis_right_top.move_relative(distance);
		
	// 	chassis_left_top.move_relative(distance*-1);
	// 	chassis_left_bottom.move_relative(distance*-1);
	// }

	while (true) {
		while (true) {
			//chassis stuff
			chassis_right_bottom.move(master.get_analog(ANALOG_LEFT_Y));
			chassis_right_top.move(master.get_analog(ANALOG_LEFT_Y));
			
			chassis_left_top.move(master.get_analog(ANALOG_RIGHT_Y)*-1);
			chassis_left_bottom.move(master.get_analog(ANALOG_RIGHT_Y)*-1);

			//intake stuff
			if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
				intake_motor = 127;	
				intake_motor2 = -127;
			} else {
				intake_motor = 0;
				intake_motor2 = 0;
			}
			if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
				intake_motor = -127;
				intake_motor2 = 127;
			} else {
				intake_motor = 0;
				intake_motor2 = 0;
			}

			//lever stuff
			if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
				lever_motor = 75;
				pros::delay(4550);
			} else {
				lever_motor = 0;
			}
			if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) {
				lever_motor = -75;
				pros::delay(4300);
			} else {
				lever_motor = 0;
			}


			// lift from korvex 
			if (master.get_digital_new_press(DIGITAL_RIGHT)) {
				armIterate++;
				if (armIterate >= ARM_PRESETS_LEN) {
					armIterate = ARM_PRESETS_LEN;
				}
				armTarget = ARM_PRESETS[armIterate];
				master.print(0, 0, "arm Tar: %d", armTarget);
				arm_motor.move_absolute(armTarget, 200);
			}
			else if (master.get_digital_new_press(DIGITAL_Y)) {
				armIterate = 0;
				arm_motor.move_absolute(20, 200);
			}
		};
	}
	pros::delay(20);
}