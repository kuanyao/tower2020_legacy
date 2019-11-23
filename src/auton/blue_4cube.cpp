#include "robot.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void blue_4cube() {
    chassis.setMaxVelocity(70);
    chassis.moveDistance(10_in);
    chassis.turnAngle(90);
}
