/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __WIFI_H__
#define __WIFI_H__
#include "generator.hh"

class Wifi: public Generator {
private:
    const char* INTERFACE = "wlan0";
    struct winfo
    {
        std::string essid;
        int quality;
        bool is_connected;
    };

    winfo collect();
public:
    std::string generate_json();
 };
#endif
