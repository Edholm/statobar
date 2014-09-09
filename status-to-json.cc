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
#include "wifi.hh"
#include "memory.hh"
#include "cpu.hh"

using namespace std;

int main(int argc, char *argv[])
{
    vector<unique_ptr<Generator>> generators;
    generators.push_back(unique_ptr<CPU>(new CPU()));
    generators.push_back(unique_ptr<Memory>(new Memory()));
    generators.push_back(unique_ptr<Wifi>(new Wifi()));
    generators.push_back(unique_ptr<Battery>(new Battery()));
    generators.push_back(unique_ptr<Volume>(new Volume()));
    generators.push_back(unique_ptr<DateTime>(new DateTime()));

    //while(true) {
        for(unsigned int i = 0; i < generators.size(); i++)
            cout << generators.at(i)->generate_json() << endl;
    //    sleep(2);
    //}
}
