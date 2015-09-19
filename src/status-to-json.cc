/* A simple dumb version of Conky suited for MY needs.
 *
 * To compile: $ make
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <iostream>
#include <vector>
#include <memory>
#include <signal.h>
#include <chrono>
#include <thread>
#include "battery.hh"
#include "generator.hh"
#include "datetime.hh"
#include "volume.hh"
#include "wifi.hh"
#include "memory.hh"
#include "cpu.hh"
#include "vpn.hh"

using namespace std;

void signal_handler(int signum)
{
    // We only need to catch these to interrupt sleep(x);
}

int main(int argc, char *argv[])
{
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    vector<unique_ptr<Generator>> generators;
    generators.push_back(unique_ptr<CPU>(new CPU()));
    generators.push_back(unique_ptr<Memory>(new Memory()));
    generators.push_back(unique_ptr<Wifi>(new Wifi()));
    generators.push_back(unique_ptr<VPN>(new VPN()));
    generators.push_back(unique_ptr<Battery>(new Battery()));
    generators.push_back(unique_ptr<Volume>(new Volume()));
    generators.push_back(unique_ptr<DateTime>(new DateTime()));

    cout << "{\"version\":1}\n[[],\n";
    fflush(stdout);
    // We need to wait for a bit to let i3bar recognize the protocoll,
    // otherwise we'll have to wait one cycle for it to output the blocks.
    this_thread::sleep_for(chrono::milliseconds(50));

    while(true) {
        cout << "[";
        for(unsigned int i = 0; i < generators.size(); i++) {
            string content = generators.at(i)->generate_json();
            if(content.empty()) {
                continue;
            }
            cout << content;
            if(i+1 < generators.size()) {
                cout << ", ";
            }
        }
        cout << "]," << endl;
        sleep(2);
    }
    cout << "]" << endl;
}
