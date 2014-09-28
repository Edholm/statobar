/* Provides common utilities
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <fstream>
#include <math.h>
#include <map>
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

string Common::map_to_json(map<string, string> m) {
    string json = "{ ";
    for (map<string, string>::iterator p = m.begin(); p != m.end(); ++p ) {
        json += "\"" + p->first + "\" : ";
        if(p->first == "full_text" || p->first == "color") {
            json += "\"" + p->second + "\"";
        } else {
            json += p->second;
        }

        if ((p != m.end()) && (next(p) != m.end())) {
            // If we're not on the last element, add comma.
            json += ", ";
        }
    }
    json += " }";
    return json;
}

string Common::filler_json(string full_text, string color) {
    map<string, string> filler;
    filler["color"] = color;
    filler["separator"] = "false";
    filler["separator_block_width"] = "0";
    filler["full_text"] = full_text;
    return Common::map_to_json(filler) + ", ";
}
