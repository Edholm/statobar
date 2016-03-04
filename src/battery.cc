/* Generates the battery info
 * Reads the info from /proc
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include "battery.hh"
#include "common.hh"

using namespace std;

#define BATT_FULL_ICO "\uf240"
#define BATT_HALF_ICO "\uf242"
#define BATT_QUARTER_ICO "\uf243"
#define BATT_3QUARTER_ICO "\uf241"
#define BATT_EMPTY_ICO "\uf244"
#define BATT_CHARGING_ICO "\uf1e6"

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
            status.append(BATT_CHARGING_ICO "  ");
            color = COLOR_GOOD;
            break;
        case DISCHARGING:
            if(bat0.percent > 78) {
                color = COLOR_GOOD;
                status.append(BATT_FULL_ICO " ");
            } else if(bat0.percent >= 55) {
                color = COLOR_DEFAULT;
                status.append(BATT_3QUARTER_ICO " ");
            } else if(bat0.percent >= 26) {
                status.append(BATT_HALF_ICO " ");
                color = COLOR_DEFAULT;
            } else if(bat0.percent >= 10) {
                status.append(BATT_QUARTER_ICO " ");
                color = COLOR_WARN;
            } else {
                color = COLOR_CRIT;
                status.append(BATT_EMPTY_ICO " ");
            }
            break;
        default:
            status.append(BATT_FULL_ICO " ");
            color = COLOR_DEFAULT;
            break;
    }
    string filler = Common::filler_json(" ");

    status.append(to_string(bat0.percent) + "% ");
    map<string, string> m;
    //m["full_text"] = status.append(Common::make_bar(bat0.percent, 10)) + " ";
    m["full_text"] = status;
    m["color"] = color;

    return filler + ", " + Common::map_to_json(m);
}


