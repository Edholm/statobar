/* Retrieve memory statistics.
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
*/

#include <string>
#include <iostream>
#include <fstream>
#include "memory.hh"
#include "common.hh"

using namespace std;

string Memory::generate_json() {
    meminfo info;
    
    ifstream file("/proc/meminfo", ios::binary);
    string line;
    if(file.good()) {
        while(getline(file, line)) {
            if (line.compare(0, 9, "MemTotal:") == 0) {
                sscanf(line.c_str(), "%*s %llu", &info.memmax);
            } else if (line.compare(0, 8, "MemFree:") == 0) {
                sscanf(line.c_str(), "%*s %llu", &info.memfree);
            } else if (line.compare(0, 8, "Buffers:") == 0) {
                sscanf(line.c_str(), "%*s %llu", &info.buffers);
            } else if (line.compare(0, 7, "Cached:") == 0) {
                sscanf(line.c_str(), "%*s %llu", &info.cached);
            } else if (line.compare(0, 6, "Shmem:") == 0) {
                sscanf(line.c_str(), "%*s %llu", &info.shmem);
            } else if (line.compare(0, 13, "SReclaimable:") == 0) {
                sscanf(line.c_str(), "%*s %llu", &info.sreclaimable);
            }
        }
    } else {
        fprintf(stderr, "Unable to read /proc/meminfo\n");
        return "";
    }
    file.close();
    info.memfree = info.memfree + info.buffers + info.cached - info.shmem + info.sreclaimable;
    info.mem = info.memmax - info.memfree;
    
    int usage = info.mem * 100 / info.memmax;
    return "Mem: " + Common::make_bar(usage);
};
