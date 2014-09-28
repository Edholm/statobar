/* Base class for all generator classes. I.e. those the collect and outputs
 * the information.
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <string>

class Generator {
public:
    virtual std::string generate_json() =0;
};
#endif
