#include "main.h"
#include "okapi/api.hpp"
#include "robot.hpp"
#include "recording.h"

using namespace okapi;
using namespace pros;

void disabled() {}

void competition_initialize() {

}

void opcontrol() {
	while (true) {
		auton_simulator();

		//chassis stuff
		chassis_control();

		//intake
		intake_control();

		//lever stuff
		lever_control();

		// lift from korvex
		arm_control();
		
		arm_control2();
		
		recording::record();
		pros::delay(ITERATION_INTERVAL);
	}
}
