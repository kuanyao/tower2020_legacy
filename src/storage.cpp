#include "storage.h"
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <istream>

namespace storage {
    using namespace std;
    using namespace recording;
    
    static const char * path = "/usd/";
    map<string, vector<RecordUnit>> all_programs;

    bool is_slot_taken(const char * slot_name) {
        return all_programs.count(slot_name) == 1;
    }

    bool save_to_slot(vector<RecordUnit> &recording, const char * slot_name) {
        string program_path = path;
        program_path = program_path + slot_name + ".data";
        ofstream program_file;
        program_file.open(program_path);
        if (program_file.is_open()) {
            cout << "begin to write to " << program_path << endl;
        } else {
            cout << "!! unable to open file for " << program_path << endl;
            return false;
        }
        int num_of_rec = recording.size();
        cout << "about to write " << num_of_rec << " lines of data." << endl;
        for (int i=0; i<num_of_rec; ++i) {
            auto ru = recording[i];
            program_file << ru.tick << " ";
            for (int j=0; j<ru.units.size(); ++j) {
                program_file << ru.units[j] << " ";
            }
            program_file << endl;
            cout << ".";
        }
        cout << "done." << endl;
        program_file.close();
        all_programs.insert_or_assign(slot_name, recording);
        return true;
    }

    void clear_slot(const char * slot_name) {
        RecordUnit temp;
        vector<RecordUnit> v = {temp};
        save_to_slot(v, slot_name);
        all_programs.erase(slot_name);
    }

    vector<RecordUnit>& get_program(const char * program_name) {
        return all_programs.at(program_name);
    }

    bool endsWith(const std::string &mainStr, const std::string &toMatch) {
        return (mainStr.size() >= toMatch.size() && mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0);
    }

    void load_program(const filesystem::path& path) {
        string line;
        std::ifstream infile(path);
        vector<RecordUnit> rus;
        if (infile.is_open()) {
            cout << "open file " << path << ", ready to read" << endl;
        } else {
            return;
        }
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            RecordUnit ru;
            iss >> ru.tick;
            for (int num; iss >> num; ) {
                ru.units.push_back(num);
            }
            rus.push_back(ru);
            cout << ".";
        }
        cout << "done." << endl;
        if (rus.size() > 1) {
            string filename = path.filename();
            all_programs.insert_or_assign(filename.substr(0, filename.size() - 5), rus);
        }
        infile.close();
    }

    void load_all_programs() {

	    vector<string> slot_names = {
            "Alpha", "Bravo", "Charlie", "Delta", "Echo",
            "Foxtrot", "Golf", "Hotel", "India", "Juliett",
            "Kilo", "Lima", "Mike", "November", "Oscar",
            "Papa", "Quebec", "Romeo", "Sierra", "Tango",
            "Uniform", "Victor", "Whiskey",
            "Xray", "Yankee", "Zulu"
	    };

        cout << "try to load all programs on disk" << endl;
        for (int i=0; i<slot_names.size(); ++i) {
            filesystem::path p("/usd/" + slot_names[i] + ".data");
            load_program(p);
        }
        cout << "finished loading." << endl;
    }
}