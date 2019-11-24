#ifndef __ROBOT_HPP
#define __ROBOT_HPP

#include "main.h"
#include "pros/misc.h"
#include "okapi/api.hpp"

//chassis motor ports
const int CHASSIS_LEFT_FRONT  = 19;
const int CHASSIS_LEFT_REAR   = 20;
const int CHASIIS_RIGHT_FRONT = 12;
const int CHASSIS_RIGHT_REAR  = 11;

//inkate motor ports
const int INTAKE_MOTOR_LEFT   = 14;
const int INTAKE_MOTOR_RIGHT  = 15;

//lever motor 
const int LEVER_MOTOR = 16;

//arm motor
const int ARM_MOTOR = 18;


//arm varibles
const int ARM_PRESETS[5]  = {0, -868, -1020, -1305, -1725};
const int ARM_PRESETS_LEN = 5;

//chassis
extern pros::Motor chassis_left_front;
extern pros::Motor chassis_left_rear;
extern pros::Motor chassis_right_front;
extern pros::Motor chassis_right_rear;
extern pros::Motor intake_motor_left;
extern pros::Motor intake_motor_right;
extern pros::Motor lever_motor;
extern pros::Motor arm_motor;
extern pros::Controller master;
extern okapi::ChassisControllerIntegrated chassis;
extern okapi::AsyncPosIntegratedController arm;
extern okapi::AsyncPosIntegratedController lever;



extern int autonSelection;

void blue_1cube();
void blue_4cube();
void red_1cube();
void red_4cube();
void skill1();
void skill2();

void chassis_tank_drive(float left, float right);

void chassis_control();
void intake_drive(float left_intake_speed, float right_intake_speed);
void arm_drive(int pos);

void intake_control();

void lever_drive(float lever_speed);
void lever_control();
void arm_control();

#endif