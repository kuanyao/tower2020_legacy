#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void red_4cube() {
    chassis.setMaxVelocity(100);
    intake_drive(140,140);
    pros::delay(600);
    intake_drive(-80,-80);
    pros::delay(100);
    intake_drive(0,0);
    pros::delay(700);
    chassis.moveDistance(17.5_in);

    chassis.setMaxVelocity(90);
    intake_drive(100, 100);
    pros::delay(400);

    chassis.moveDistance(38_in);
    pros::delay(400);
    intake_drive(35,35);
    pros::delay(100);
    chassis.setMaxVelocity(120);
    chassis.moveDistance(-51_in);
    pros::delay(570);
    chassis.setMaxVelocity(150);
    chassis.turnAngle(-130.5_deg);
    intake_drive(-200,-200);
    pros::delay(120);
    intake_drive(0,0);
    lever_drive(200);
    chassis.moveDistance(14.5_in);
    pros::delay(2400);
    lever_drive(0);
    chassis.setMaxVelocity(170);
    chassis.moveDistance(4_in);
    intake_drive(-200,-200);
    chassis.setMaxVelocity(90);
    chassis.moveDistance(-12_in);
    intake_drive(0,0);

}