/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#ifndef __CPU_H__
#define __CPU_H__
#include "generator.hh"

class CPU: public Generator {
public:
    std::string generate_json();
};

#endif
