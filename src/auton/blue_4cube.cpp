#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void blue_4cube() {
    chassis.setMaxVelocity(80);
    intake_drive(100, 100);
    // chassis.moveDistance(10_in);
    // chassis.moveDistance(-10_in);
    // arm_drive(4);
    // pros::delay(3000);
    // arm_drive(0);
    // pros::delay(2000);
    // chassis.turnAngle(-5);
    //intake_drive(-200,200);     
    //chassis.moveDistance(5_in);
    // pros::delay(10);
    chassis.moveDistance(26_in);
    chassis.moveDistance(24_in);
    pros::delay(1000);
    intake_drive(0,0);
    chassis.setMaxVelocity(200);
    chassis.moveDistance(-48.5_in);
    pros::delay(500);
    chassis.setMaxVelocity(30);
    chassis.moveDistance(-9.5_in);
    chassis.moveDistance(7.5_in);
    chassis.turnAngle(114.5_deg);
    intake_drive(-50,-50);
    pros::delay(300);
    intake_drive(0,0);
    chassis.moveDistance(12_in);
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


    //chassis.turnAngle(90_deg);
    
}
