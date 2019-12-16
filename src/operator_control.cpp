#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"

using namespace okapi;
using namespace pros;


//where the arm is
int armPos = 0;

//presets
void arm_control() {
	int armTarget = 0;
	int armIterate = 0;
	
	if (master.get_digital_new_press(DIGITAL_RIGHT)) {
		//descore high
		arm_drive(3);
		armPos = 3;
	} else if (master.get_digital_new_press(DIGITAL_UP)) {
		//score high
		arm_drive(4);
		armPos = 4;
	} else if (master.get_digital_new_press(DIGITAL_LEFT)) {
		//descore low
		arm_drive(1);
		armPos = 1;
	} else if(master.get_digital_new_press(DIGITAL_DOWN)) {
		//score low
		arm_drive(2);
		armPos = 2;
	} else if (master.get_digital_new_press(DIGITAL_Y) == 1 && !armPos == 0) {
		//original pos
		armIterate = 0;
		armPos = 0;
		arm_motor.move_voltage(12000);
		pros::delay(500);
		arm_motor.move_voltage(0);
	} 
}

//manual drive for arm
void arm_control2() {
	
	if(master.get_digital(E_CONTROLLER_DIGITAL_B)) {

		arm_motor.move_voltage(-12000);
		arm_motor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		// pros::delay(50);
		// arm_motor.move_voltage(0);
	} else if (master.get_digital(E_CONTROLLER_DIGITAL_A)) {

		arm_motor.move_voltage(5000);
		arm_motor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		// pros::delay(50);
		// arm_motor.move_voltage(0);

	} else if (master.get_digital(E_CONTROLLER_DIGITAL_X)) {

		arm_motor.set_brake_mode(E_MOTOR_BRAKE_COAST);
		arm_motor.move_voltage(7000);
		pros::delay(400);
		arm_motor.move_voltage(0);

	}  else if (armPos == 0) {
		//so arm control 1&2 dont collide
		arm_motor.move_voltage(0);
	}

}
//for chassis
void chassis_control() {
	int left_power = master.get_analog(ANALOG_LEFT_Y);
	int right_power = master.get_analog(ANALOG_RIGHT_Y);
	chassis_tank_drive(right_power, -left_power);
}
//intake
void intake_control() {
	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
		intake_drive(200, 200);
	} else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && armPos == 0) {
		intake_drive(-100,-100);
	} else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && armPos > 0) {
		//slower for scoring in towers
		pros::delay(15);
		intake_drive(-85,-85);
	} else {
		intake_drive(0,0);
	}
}

void lever_control() {
	if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		lever_drive(-200);
		//intake pushes out lever slightly
		intake_drive(-15, -15);
	} else if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		lever_drive(200);
		intake_drive(75, 75);
	} else {
		lever_drive(0);
	}
}

