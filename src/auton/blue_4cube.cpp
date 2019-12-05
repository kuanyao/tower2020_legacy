#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void blue_4cube() {
    // arm_drive(4);
    // pros::delay(1000);
    // arm_drive(0);

    // chassis.setMaxVelocity(80);
    // intake_drive(100, 100);

    // chassis.moveDistance(50.5_in);
    // pros::delay(1000);
    // intake_drive(0,0);
    // chassis.setMaxVelocity(150);
    // chassis.moveDistance(-45_in);
    // pros::delay(500);
    // chassis.setMaxVelocity(100);
    // chassis.turnAngle(115.5_deg);
    // intake_drive(-200,-200);
    // pros::delay(200);
    // intake_drive(0,0);
    // chassis.moveDistance(15.5_in);
    // lever_drive(200);
    // pros::delay(2500);
    // lever_drive(0);
    // chassis.setMaxVelocity(200);
    // chassis.moveDistance(2_in);
    // intake_drive(-200,200);
    // pros::delay(400);
    // intake_drive(0,0);
    // chassis.setMaxVelocity(90);
    // chassis.moveDistance(-8_in);
    chassis.setMaxVelocity(150);//
    intake_drive(100, 100);
    pros::delay(500);
    chassis.moveDistance(25.5_in);
    pros::delay(700);
    chassis.moveDistance(25_in);
    intake_drive(0,0);

    chassis.setMaxVelocity(100); //

    chassis.turnAngle(-33.5_deg);
    chassis.moveDistance(-48.5_in);
    chassis.turnAngle(36.5_deg);
    chassis.moveDistance(-4_in);

    intake_drive(100, 100);
    chassis.moveDistance(50.5_in);
    pros::delay(1000);
    intake_drive(0,0);
    chassis.moveDistance(-45_in);
    pros::delay(500);
    chassis.setMaxVelocity(200); // 
    chassis.turnAngle(115.5_deg);
    intake_drive(-50,-50);
    pros::delay(200);
    intake_drive(0,0);
    chassis.moveDistance(15.5_in);
    lever_drive(200);
    pros::delay(3400);
    lever_drive(0);
    chassis.setMaxVelocity(200); // 
    chassis.moveDistance(2_in);
    intake_drive(-200,-200);
    pros::delay(400);
    intake_drive(0,0);
    chassis.setMaxVelocity(200); // 
    chassis.moveDistance(-15_in);

}
