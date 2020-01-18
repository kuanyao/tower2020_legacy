#ifndef __ROBOT_HPP
#define __ROBOT_HPP

#include "main.h"
#include "pros/misc.h"
#include "okapi/api.hpp"

//chassis motor ports
const int CHASSIS_LEFT_FRONT  = 1;
const int CHASSIS_LEFT_REAR   = 12;
const int CHASIIS_RIGHT_FRONT = 14;
const int CHASSIS_RIGHT_REAR  = 13;

//inkate motor ports
const int INTAKE_MOTOR_LEFT   = 15;
const int INTAKE_MOTOR_RIGHT  = 11;

//lever motor 
const int LEVER_MOTOR = 20;

//arm motor
const int ARM_MOTOR = 10;

//arm varibles
const int ARM_PRESETS[5]  = {0, -666, -734, -845, -1025};
const int ARM_PRESETS_LEN = 5;

//chassis
// extern okapi::Motor chassis_left_front;
// extern okapi::Motor chassis_left_rear;
// extern okapi::Motor chassis_right_front;
// extern okapi::Motor chassis_right_rear;
extern okapi::Motor intake_motor_left;
extern okapi::Motor intake_motor_right;
extern okapi::Motor lever_motor;
extern okapi::Motor arm_motor;
extern pros::Controller master;
extern okapi::ChassisControllerIntegrated chassis;

//functions 
void chassis_tank_drive(int left, int right);

void chassis_control();
void intake_drive(float left_intake_speed, float right_intake_speed);
void arm_drive(int pos);

void intake_control();

void lever_drive(float lever_speed);
void lever_control();
void arm_control();
void arm_control2();
void auton_simulator();

#endif