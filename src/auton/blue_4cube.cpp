#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

//tune
const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 11.5_in;


auto chassis = ChassisControllerFactory::create(CHASSIS_LEFT_FRONT, CHASSIS_LEFT_REAR, -CHASIIS_RIGHT_FRONT, -CHASSIS_RIGHT_REAR, AbstractMotor::gearset::green,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);


void blue_4cube() {
    chassis.moveDistance(12_in);
}