#ifndef __RECORDING_H
#define __RECOORDING_H

#include <vector>

namespace okapi {
    class AbstractMotor;
}

namespace recording {
    struct RecordUnit {
        short tick;
        std::vector<int> units;
        // short left;
        // short right;
        // short lever;
        // short left_intake;
        // short right_intake;
        // short arm;
    } ;

    void reset(int duration, int interval, void (*post_record_action)(void));
    void record();
    void printout();
    void replay();
    void set_replay_loader(std::vector<RecordUnit>& (*)(void));
    void set_motor_group(std::vector<okapi::AbstractMotor*>&);
    // void init(std::vector<int>& (*input_device)(void), void (*output_device)(std::vector<int>&), std::vector<RecordUnit>& (*replay_loader)(void));
    std::vector<RecordUnit>& dump();
}

#endif
