/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "generator.hh"

class Memory: public Generator {
public:
    std::string generate_json();
};

#endif
