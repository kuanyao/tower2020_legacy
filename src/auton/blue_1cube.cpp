#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void blue_1cube() {
chassis.setMaxVelocity(95);
    intake_drive(100,100);
    pros::delay(500);
    intake_drive(-80,-80);
    pros::delay(120);
    intake_drive(0,0);
    pros::delay(750);
    chassis.moveDistance(7.5_in);

    chassis.setMaxVelocity(90);
    intake_drive(120, 120);
    pros::delay(400);

    chassis.moveDistance(40_in);
    pros::delay(100);
    intake_drive(35,35);
    chassis.setMaxVelocity(100);
    chassis.moveDistance(-26_in);
    pros::delay(500);
    chassis.setMaxVelocity(120);
    pros::delay(300);
    chassis.turnAngle(-80_deg);
    intake_drive(-200,-200);
    pros::delay(300);
    intake_drive(80,80);
    chassis.moveDistance(24.5_in);
    intake_drive(30,30);
    pros::delay(300);
    chassis.moveDistance(-7_in);

    intake_drive(-200,-200);
    pros::delay(150);
    intake_drive(20,20);
    chassis.turnAngle(-73_deg);
    lever_drive(200);
    chassis.setMaxVelocity(100);
    chassis.moveDistance(18_in);
    pros::delay(2200);
    lever_drive(0);
    intake_drive(-200,-200);
    chassis.setMaxVelocity(90);
    chassis.moveDistance(-12_in);
    intake_drive(0,0);
}