/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#ifndef __BATTERY_H__
#define __BATTERY_H__
#include <string.h>

class Battery {
private:
    enum battery_state : int {
        CHARGING,
        DISCHARGING,
        FULL,
        UNKNOWN
    };
    struct battery {
        int percent;
        battery_state state;
    };
    const std::string BAT0_PATH = "/sys/class/power_supply/BAT0/";
    const std::string ENERGY_NOW_FILE = "energy_now";
    const std::string ENERGY_FULL_FILE = "energy_full";
    const std::string STATUS_FILE = "status";

    battery bat0;

    void init();
public:
    std::string battery_json();
    Battery();
};
#endif
