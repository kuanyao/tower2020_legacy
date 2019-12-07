#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void blue_4cube() {
    chassis.setMaxVelocity(95);
    intake_drive(140,140);
    pros::delay(400);
    intake_drive(-80,-80);
    pros::delay(100);
    intake_drive(0,0);
    pros::delay(500);
    chassis.moveDistance(17.5_in);

    chassis.setMaxVelocity(90);
    intake_drive(140, 140);
    pros::delay(400);

    chassis.moveDistance(37_in);
    pros::delay(400);
    intake_drive(35,35);
    chassis.setMaxVelocity(100);
    chassis.moveDistance(-39_in);
    pros::delay(500);
    chassis.setMaxVelocity(150);
    chassis.turnAngle(145.5_deg);
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
    // chassis.setMaxVelocity(200);//
    // intake_drive(100, 100);
    // pros::delay(500);
    // chassis.moveDistance(55.5_in);
    // intake_drive(0,0);

    // chassis.setMaxVelocity(200); //

    // chassis.turnAngle(-35.5_deg);
    // chassis.moveDistance(-52.5_in);
    // pros::delay(400);
    // chassis.turnAngle(55.5_deg);

    // intake_drive(100, 100);
    // chassis.moveDistance(50.5_in);
    // pros::delay(1000);
    // intake_drive(0,0);
    // chassis.moveDistance(-45_in);
    // pros::delay(500);
    // chassis.setMaxVelocity(200); // 
    // chassis.turnAngle(115.5_deg);
    // intake_drive(-50,-50);
    // pros::delay(200);
    // intake_drive(0,0);
    // chassis.moveDistance(15.5_in);
    // lever_drive(200);
    // pros::delay(3400);
    // lever_drive(0);
    // chassis.setMaxVelocity(200); // 
    // chassis.moveDistance(2_in);
    // intake_drive(-200,-200);
    // pros::delay(400);
    // intake_drive(0,0);
    // chassis.setMaxVelocity(200); // 
    // chassis.moveDistance(-15_in);

}
