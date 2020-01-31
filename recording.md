# How to port the replay logic

1. Copy these files into the project

    ```bash
    include
    ├── recording.h
    ├── screen.h
    └── storage.h

    src
    ├── recorder.cpp
    ├── screen.cpp
    └── storage.cpp
    ```

1. Define the iternation interval in a common header file. The iteration interval is used during the recording and replaying. If this is changed, all saved programs must be cleared. Otherwise, it is possible to damage the motors. This definision can be put in a common header file, e.g., `main.h`

    ```c
    const int ITERATION_INTERVAL = 50;
    ```

1. Include the following header files into your main body cpp file:

    ```c
    #include "screen.h"
    #include "storage.h"
    ```

1. add automoous play:

    ```c++
    void autonomous() {
        recording::replay();
    }
    ```

1. Add the recording logic into the dirver controls' main loop:

    ```c++
    void opcontrol() {
        while (true) {
            auton_simulator(); // optionally you may add a auton trigger logic
            // ...
            recording::record();
            pros::delay(ITERATION_INTERVAL);
        }
    }
    ```

1. Add auton simulator into the driver controls's loop. This helps to trigger the auton program without using the compitition switch.

    ```c++
    void auton_simulator() {
        if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
            int x_power = master.get_analog(ANALOG_RIGHT_X);
            if (abs(x_power) > 120) {
                autonomous();
            }
        }
    }
    ```

1. Add the following lines into the `initialize()` method:

    ```c++
    void initialize()
    {
        screen::setup_screen(); // set up the screen buttons
        screen::set_notif_handler(notify_controller); // hook up the screen notification to the controller, e.g., rumble
        storage::load_all_programs(); // load all saved programs from the storage device
        recording::set_motor_group(get_motor_group()); // tell the recording device which motor to record, and how to replay

        // you may add your own initialize steps; but do not chnage the screen
    }
    ```

1. add the screen notification handler. This step is optional, but gives you better experience by providing feedback to the controller. e.g., when a program recording starts, you can rumble the controller.

    ```c++
    void notify_controller(const char * rumble_msg, const char * msg) {
        master.rumble(rumble_msg);  // rumble the controller
        master.print(0, 0, "%s", msg); // display a text message to the screen. note this line doesn't work. 
    }
    ```

1. get motor groups that needs to be recorded. the function name doesnt matter, but the return type must be the same.

    ```c++
    vector<AbstractMotor*>& get_motor_group() { // must return a vector of motors (type must be okapi::AbstractMotor)

        // usually you will have 8 motors, but if you choose okapi chassis controller, the chassis use 2 motor groups that 
        // take or send values to 2 motors in each group. So only 2 motor groups are needed.
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
    ```
