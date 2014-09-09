/* A simple dumb version of Conky suited for MY needs.
 *
 * To compile: $ make
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <iostream>
#include "battery.hh"

using namespace std;

int main(int argc, char *argv[])
{
    Battery* bat0 = new Battery();
    cout << bat0->battery_json();
}
