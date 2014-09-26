/* Generates the battery info
 * Reads the info from /proc
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "battery.hh"
#include "common.hh"

using namespace std;

void Battery::collect()
{
    string state = Common::read_first_line(BAT0_PATH + STATUS_FILE);
    if (state == "Charging")
        bat0.state = CHARGING;
    else if (state == "Discharging")
        bat0.state = DISCHARGING;
    else if (state == "Full")
        bat0.state = FULL;
    else
        bat0.state = UNKNOWN;

    long now = atol(Common::read_first_line(BAT0_PATH + ENERGY_NOW_FILE).c_str());
    long full = atol(Common::read_first_line(BAT0_PATH + ENERGY_FULL_FILE).c_str());
    bat0.percent = static_cast<int>(((double)now / full) * 100 + 0.5);
}

string Battery::generate_json() {
    this->collect();
    string status, color;
    switch(bat0.state) {
        case CHARGING:
            status.append("  ");
            color = COLOR_GOOD;
            break;
        case DISCHARGING:
            status.append("◯ ");
            if(bat0.percent >= 70) {
                color = COLOR_GOOD;
            } else if(bat0.percent >= 40) {
                color = COLOR_DEFAULT;
            } else if(bat0.percent >= 20) {
                color = COLOR_WARN;
            } else {
                status.append(to_string(bat0.percent) + "% ");
                color = COLOR_CRIT;
            }
            break;
        default:
            status.append("● ");
            color = COLOR_DEFAULT;
            break;
    }
    string filler = Common::filler_json(" ");

    map<string, string> m;
    m["full_text"] = status.append(Common::make_bar(bat0.percent, 10)) + " ";
    m["color"] = color;

    return filler + Common::map_to_json(m);
}


