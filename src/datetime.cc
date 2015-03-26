/* Formates date/time
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <ctime>
#include <map>
#include "datetime.hh"
#include "common.hh"

#include <iostream>

using namespace std;

string DateTime::current_datetime() {
    setlocale(LC_TIME, "");
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);

    unsigned int buff_size = 25;
    char buffer [buff_size];
    strftime (buffer, buff_size, "%A %d %b %R", timeinfo);
    return buffer;
}

string DateTime::generate_json() {
    map<string, string> m;

    m["full_text"] = "   " + current_datetime();
    m["color"] = COLOR_DEFAULT;
    m["separator"] = "false";
    return Common::map_to_json(m);
}
