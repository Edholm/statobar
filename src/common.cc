/* Provides common utilities
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <string>
#include <fstream>
#include <math.h>
#include "common.hh"
using namespace std;

// Used for reading /sys and /proc files.
string Common::read_first_line(string filename) {
    ifstream file(filename.c_str(), ios::binary);
    string line;
    if(file.good()) {
        getline(file, line);
    }
    file.close();
    return line;
}

string Common::make_bar(int usage, int width, string tick_full, string tick_empty) {
    string bar;
    int scaledusage = rint(usage * width / 100), i;

    for (i = 0; i < scaledusage; i++)
        bar.append(tick_full);

    for (; i < width; i++)
        bar.append(tick_empty);

    return bar;
}
