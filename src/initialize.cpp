#include "api.h"
#include "robot.hpp"
#include "okapi/api.hpp"
#include "screen.h"
#include "storage.h"

using namespace std;
using namespace pros;
using namespace okapi;

okapi::Motor intake_motor_left(INTAKE_MOTOR_LEFT);
okapi::Motor intake_motor_right(INTAKE_MOTOR_RIGHT);
okapi::Motor lever_motor(LEVER_MOTOR, false, AbstractMotor::gearset::red);
okapi::Motor arm_motor(ARM_MOTOR, false, AbstractMotor::gearset::red);
pros::Controller master (E_CONTROLLER_MASTER);

/* choose only one of the following: either separated chassis motors, or the chassis controller */
//chassis motors
// okapi::Motor chassis_right_rear(CHASSIS_RIGHT_REAR);
// okapi::Motor chassis_right_front(CHASIIS_RIGHT_FRONT);
// okapi::Motor chassis_left_rear(CHASSIS_LEFT_REAR);
// okapi::Motor chassis_left_front(CHASSIS_LEFT_FRONT);

const auto WHEEL_DIAMETER = 4.5_in;
const auto CHASSIS_WIDTH = 9.3_in;

// chassis controller
okapi::ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
  {-CHASSIS_LEFT_FRONT, -CHASSIS_LEFT_REAR}, 
  {CHASIIS_RIGHT_FRONT, CHASSIS_RIGHT_REAR},
  AbstractMotor::gearset::green,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);

/* choose only one of the following: either separated chassis motors, or the chassis controller 
AsyncPosIntegratedController arm = AsyncControllerFactory::posIntegrated(ARM_MOTOR);
AsyncPosIntegratedController lever = AsyncControllerFactory::posIntegrated(LEVER_MOTOR);
*/

vector<AbstractMotor*>& get_motor_group() {
	static vector<AbstractMotor*> motor_group;

	auto left_motor = ((SkidSteerModel *)chassis.getChassisModel().get())->getLeftSideMotor();
	auto right_motor = ((SkidSteerModel *)chassis.getChassisModel().get())->getRightSideMotor();

	motor_group.push_back(left_motor.get());
	motor_group.push_back(right_motor.get());
	motor_group.push_back(&intake_motor_left);
	motor_group.push_back(&intake_motor_right);
	motor_group.push_back(&lever_motor);
	motor_group.push_back(&arm_motor);
	return motor_group;
}

void notify_controller(const char * rumble_msg, const char * msg) {
	master.rumble(rumble_msg);
	master.print(0, 0, "%s", msg);
}

void initialize()
{
	screen::setup_screen();
	screen::set_notif_handler(notify_controller);
	storage::load_all_programs();
	recording::set_motor_group(get_motor_group());
}
