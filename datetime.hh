/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#ifndef __DATETIME_H__
#define __DATETIME_H__
#include "generator.hh"

class DateTime: public Generator {
private:
    std::string current_datetime();
public:
    std::string generate_json();
};
#endif
