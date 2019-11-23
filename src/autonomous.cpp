#include "robot.hpp"

void autonomous()
{
    int autonStart = pros::millis(); // note the start time
    int auton = 5;

    if (autonSelection != 10)
    {
        auton = autonSelection; // this is to enable auton selector
    }

    switch (auton)
    {
    case 5: // test
        break;
    case 0: // skills 18
        skill1();
        break;
    case 10:
        skill2();
        break;
    case 20:
        skill3();
        break;
    case 1: 
        blue_4cube();
        break;
    case 2: 
        blue_1cube();
        break;
    case 3: 
        break;
    case -1: // red close, mid and top flag and park chassis.setMaxVelocity(180);
        red_4cube();
        break;
    case -2: // red full post and park only
        red_1cube();
        break;
    case -3: 
        break;
    default:
        break;
    }
}
