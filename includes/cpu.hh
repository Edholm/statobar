/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#ifndef __CPU_H__
#define __CPU_H__
#include "generator.hh"

class CPU: public Generator {
private:
    unsigned int calc_usage();
    unsigned long long prev_total_jiffies, prev_work_jiffies;
public:
    std::string generate_json();
};

#endif
