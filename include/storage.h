#ifndef __STORAGE_H
#define __STORAGE_H

#include <vector>
#include "recording.h"

namespace storage {
    bool is_slot_taken(const char * slot_name);
    bool save_to_slot(std::vector<recording::RecordUnit>& recording, const char * slot_name);
    void clear_slot(const char * slot_name);
    void load_all_programs();
    std::vector<recording::RecordUnit>& get_program(const char *);
}

#endif
