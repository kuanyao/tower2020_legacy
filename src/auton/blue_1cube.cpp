#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void blue_1cube() {
    arm_drive(4);
    pros::delay(1000);
    arm_drive(0);

    pros::delay(500);
    intake_drive(-200,-200);
    chassis.moveDistance(36_in);


}