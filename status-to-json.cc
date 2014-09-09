/* A simple dumb version of Conky suited for MY needs.
 *
 * To compile: $ make
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <iostream>
#include <vector>
#include <memory>
#include "battery.hh"
#include "generator.hh"
#include "datetime.hh"
#include "volume.hh"

using namespace std;

int main(int argc, char *argv[])
{
    vector<unique_ptr<Generator>> generators;
    generators.push_back(unique_ptr<Battery>(new Battery()));
    generators.push_back(unique_ptr<Volume>(new Volume()));
    generators.push_back(unique_ptr<DateTime>(new DateTime()));

    for(unsigned int i = 0; i < generators.size(); i++)
        cout << generators.at(i)->generate_json() << endl;
}
