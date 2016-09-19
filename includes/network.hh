/*
 * Copyright 2016 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __NETWORK_H__
#define __NETWORK_H__
#include "generator.hh"

class Network: public Generator {
private:
    const char* INTERFACE = "wlp2s0";
    struct winfo
    {
        std::string essid;
        int quality;
        int8_t level;
        bool is_connected;
    };

    winfo collect();
public:
    std::string generate_json();
 };
#endif
