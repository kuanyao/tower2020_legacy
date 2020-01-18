#include "main.h"
#include "recording.h"
#include "okapi/api.hpp"

#include <exception>

namespace recording {

    using namespace std;
    bool is_power_changed();
    void do_record();

    // private variables
    vector<RecordUnit> recording;
    vector<RecordUnit>& (*replay_loader)(void);
    const int threshold = 15;
    int recording_interval = 50;
    int recording_time = 15000;
    int tick = 0;
    void (*post_record_action)(void) = NULL;

    vector<okapi::AbstractMotor*> empty_motor_group;
    vector<okapi::AbstractMotor*> * motor_group = &empty_motor_group;

    void set_motor_group(vector<okapi::AbstractMotor*>& motors) {
        motor_group = &motors;
    }

    void reset(int duration, int interval, void (*action)(void)) {
        recording_interval = interval;
        recording_time = duration;
        tick = 0;
        post_record_action = action;
        
        recording.clear();
        int capacity = duration / interval;
    }

    void set_replay_loader(std::vector<RecordUnit>& (* loader)(void)) {
        replay_loader = loader;
    }

    void record() {
        int capacity = recording_time/ recording_interval;

        if (tick == capacity - 1) {
            if (post_record_action != NULL) {
                post_record_action();
            }
            ++tick; 
            return;
        } else if (tick == capacity) {
            return;
        }

        ++ tick;

        if (is_power_changed()) {
            do_record();
        }
    }

    bool is_power_changed() {
        if (recording.size() == 0) {
            for (int i=0; i<(*motor_group).size(); ++i) {
                if (abs((*motor_group)[i]->getVoltage()) > threshold) {
                    cout << "initial position changed, "; 
                    return true;
                }
            }
        } else { 
            RecordUnit& last_unit = recording.back();
            for (int i=0; i<last_unit.units.size(); ++i) {
                if (abs(last_unit.units[i] - (*motor_group)[i]->getVoltage()) > threshold) {
                    cout << "new change detected, ";
                    return true;
                }
            }
        }
        return false;
    }

    void do_record() {
        if (recording.size() == 0) {
            tick = 0; // reset tick position
        }
        RecordUnit new_unit; 
        cout << "saving a new record " << endl; 
        new_unit.tick = tick;
        for (int i=0; i<(*motor_group).size(); ++i) {
            new_unit.units.push_back((*motor_group)[i]->getVoltage());
        }
        recording.push_back(new_unit);
    }

    void printout() {
        for (int i=0; i<=recording.size(); ++i) {
            std::cout << recording[i].tick;
            for (int j=0; j<recording[i].units.size(); ++j) {
                cout << ", " << recording[i].units[j];
            }
            cout << endl;
        }
    }

    void replay() {
        if (replay_loader == NULL) {
            cout << "no replay loader found" << endl;
            return;
        }
        vector<RecordUnit> replay_recording = replay_loader();
        if (replay_recording.empty()) {
            cout << "load empty records, nothing to replay" << endl;
            return;
        }
        cout << "about to replay " << replay_recording.size() << " steps" << endl;
        int starting_tick = replay_recording.front().tick;
        int ending_tick = replay_recording.back().tick;
        cout << "starting at " << starting_tick << " and end at " << ending_tick << " for total " 
                << (ending_tick - starting_tick) * 50 / 1000 << " senconds" << endl;

        int r_index = 0;
        for (int t = starting_tick; t < ending_tick; ++t) {
            RecordUnit& unit = replay_recording[r_index];
            int tick = unit.tick;
            if (tick == t) {
                for (int j=0; j<(*motor_group).size(); ++j) {
                    (*motor_group)[j]->moveVoltage(unit.units[j]);
                }
                r_index ++;
            }
            pros::delay(recording_interval);
        }
        cout << "replaying done !!" << endl;
    }

    vector<RecordUnit>& dump() {
        return recording;
    }
}