/*
 * Copyright 2016 Johan 'Horv' Andersson <drhorv@gmail.com>
 */
#pragma once
#ifndef __STATUS_PACKAGES__
#define __STATUS_PACKAGES__
#include "generator.hh"

class PackagesToUpdate: public Generator {
private:
    unsigned int get_nbr_pacman_packages();
    std::string exec(const char* cmd);
public:
    std::string generate_json();
};

#endif
