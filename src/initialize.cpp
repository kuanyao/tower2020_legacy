#include "api.h"
#include "robot.hpp"
#include "okapi/api.hpp"

using namespace pros;
using namespace okapi;

pros::Motor intake_motor_left(INTAKE_MOTOR_LEFT);
pros::Motor intake_motor_right(INTAKE_MOTOR_RIGHT);
pros::Motor lever_motor(LEVER_MOTOR);
pros::Motor arm_motor(ARM_MOTOR);
pros::Controller master (E_CONTROLLER_MASTER);

/* choose only one of the following: either separated chassis motors, or the chassis controller */
//chassis motors
pros::Motor chassis_right_rear(CHASSIS_RIGHT_REAR);
pros::Motor chassis_right_front(CHASIIS_RIGHT_FRONT);
pros::Motor chassis_left_rear(CHASSIS_LEFT_REAR);
pros::Motor chassis_left_front(CHASSIS_LEFT_FRONT);

const auto WHEEL_DIAMETER = 4.5_in;
const auto CHASSIS_WIDTH = 11.5_in;
// chassis controller
okapi::ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
  {-CHASSIS_LEFT_FRONT, -CHASSIS_LEFT_REAR}, {CHASIIS_RIGHT_FRONT, CHASSIS_RIGHT_REAR},
  AbstractMotor::gearset::green,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);
// /* choose only one of the following: either separated chassis motors, or the chassis controller */
// okapi::ChassisControllerIntegrated intake = ChassisControllerFactory::create(
//   {-INTAKE_MOTOR_RIGHT}, {INTAKE_MOTOR_LEFT},
//   AbstractMotor::gearset::green
// );

int autonSelection = 10;
int autonPark = 0;

static lv_res_t redBtnmAction(lv_obj_t *btnm, const char *txt)
{
	printf("red button: %s released\n", txt);

	if (txt == "4Cube")
	{
		autonSelection = -1; // or whatever red close is
	}

	if (txt == "1Cube")
	{
		autonSelection = -2;
	}

    if (txt == "Disable")
	{
		autonSelection = -3;
	}

	return LV_RES_OK; // return OK because the button matrix is not deleted
}

static lv_res_t blueBtnmAction(lv_obj_t *btnm, const char *txt)
{
	printf("blue button: %s released\n", txt);

	if (txt == "4Cube")
	{
		autonSelection = 1;
	}
	if (txt == "1Cube")
	{
		autonSelection = 2;
	}
	if (txt == "Disable")
	{
		autonSelection = 3;
	}

	return LV_RES_OK;
}

static lv_res_t skillsBtnAction(lv_obj_t *btn, const char *txt)
{
	printf("blue button: %s released\n", txt);

	if (txt == "Skill 1")
	{
		autonSelection = 0;
	}
	if (txt == "Skill 2")
	{
		autonSelection = 10;
	}
	if (txt == "Skill 3")
	{
		autonSelection = 20;
	}

	return LV_RES_OK;
}

//Create a button descriptor string array
static const char *btnmMap[] = {"4Cube", "1Cube", "Disable", ""};
static const char *btnSkillsMap[] = {"Skill 1", "Skill 2", "Skill 3", ""};

void initialize()
{
	pros::delay(50); // sometimes LVGL won't draw the screen if there is no delay or it is not inverted on the brain

	// lvgl theme
	lv_theme_t *th = lv_theme_alien_init(280, NULL); //Set a HUE value and keep font default
	lv_theme_set_current(th);

	// create a tab view object
	lv_obj_t *tabview;
	tabview = lv_tabview_create(lv_scr_act(), NULL);

	// add 3 tabs (the tabs are page (lv_page) and can be scrolled
	lv_obj_t *redTab = lv_tabview_add_tab(tabview, "Red");
	lv_obj_t *blueTab = lv_tabview_add_tab(tabview, "Blue");
	lv_obj_t *skillsTab = lv_tabview_add_tab(tabview, "Skills");

	// add content to the tabs

	// red tab

	// button matrix
	lv_obj_t *redBtnm = lv_btnm_create(redTab, NULL);
	lv_btnm_set_map(redBtnm, btnmMap);
	lv_btnm_set_toggle(redBtnm, true, 0);
	lv_btnm_set_action(redBtnm, redBtnmAction);
	lv_obj_set_size(redBtnm, 450, 50);
	lv_obj_set_pos(redBtnm, 0, 100);
	lv_obj_align(redBtnm, NULL, LV_ALIGN_CENTER, 0, 0);

	// blue tab
	lv_obj_t *blueBtnm = lv_btnm_create(blueTab, NULL);
	lv_btnm_set_map(blueBtnm, btnmMap);
	lv_btnm_set_toggle(blueBtnm, true, 0);
	lv_btnm_set_action(blueBtnm, blueBtnmAction);
	lv_obj_set_size(blueBtnm, 450, 50);
	lv_obj_set_pos(blueBtnm, 0, 100);
	lv_obj_align(blueBtnm, NULL, LV_ALIGN_CENTER, 0, 0);

	// skills tab
	lv_obj_t *skillsBtnm = lv_btnm_create(skillsTab, NULL);
	lv_btnm_set_map(skillsBtnm, btnSkillsMap);
	lv_btnm_set_toggle(skillsBtnm, true, 0);
	lv_btnm_set_action(skillsBtnm, skillsBtnAction);
	lv_obj_set_size(skillsBtnm, 450, 50);
	lv_obj_set_pos(skillsBtnm, 0, 100);
	lv_obj_align(skillsBtnm, NULL, LV_ALIGN_CENTER, 0, 0);
}
