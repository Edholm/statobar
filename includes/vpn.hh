/*
 * Copyright 2015 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __VPN_H__
#define __VPN_H__
#include "generator.hh"

class VPN: public Generator {
private:
    bool vpn_enabled();
public:
    std::string generate_json();
};
#endif
