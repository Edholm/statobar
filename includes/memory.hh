/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "generator.hh"

class Memory: public Generator {
private:
    struct meminfo {
        /* memory information in kilobytes */
        unsigned long long mem, memfree, memmax;
        unsigned long long bufmem, buffers, cached;
        unsigned long long shmem, sreclaimable;
    };
public:
    std::string generate_json();
};

#endif
