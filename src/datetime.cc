/* Formates date/time
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <string>
#include <ctime>
#include "datetime.hh"

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
    return string(current_datetime());
}
