/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __BATTERY_H__
#define __BATTERY_H__
#include "generator.hh"

class Battery: public Generator {
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
    const std::string ENERGY_NOW_FILE = "charge_now";
    const std::string ENERGY_FULL_FILE = "charge_full";
    const std::string STATUS_FILE = "status";

    battery bat0;
    void collect();
public:
    std::string generate_json();
};
#endif
