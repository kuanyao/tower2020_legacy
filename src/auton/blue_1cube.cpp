#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void blue_1cube() {
    arm_drive(4);
    pros::delay(1000);
    arm_drive(0);

    pros::delay(500);
    intake_drive(200,200);
    chassis.moveDistance(36_in);
    chassis.moveDistance(-40_in);
    pros::delay(500);
    chassis.moveDistance(10_in);
    chassis.turnAngle(-105);
    chassis.moveDistance(10_in);

    lever_drive(200);
    pros::delay(2500);
    lever_drive(0);
    chassis.setMaxVelocity(200);
    chassis.moveDistance(2_in);
    intake_drive(-200,200);
    pros::delay(300);
    intake_drive(0,0);
    chassis.setMaxVelocity(90);
    chassis.moveDistance(-5_in);
}