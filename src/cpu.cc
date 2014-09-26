/* Retrieve CPU usage statistics.
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
*/

#include <string>
#include <fstream>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include "cpu.hh"
#include "common.hh"

using namespace std;
using namespace boost;

string CPU::generate_json() {
    string stat = Common::read_first_line("/proc/stat");
    unsigned long long total_jiffies = 0, work_jiffies = 0;
    vector<string> jiffies_str;
    split(jiffies_str, stat, is_any_of(" "), token_compress_on);

    for(unsigned int i = 1; i < jiffies_str.size(); i++) {
        unsigned int tmp = lexical_cast<unsigned int>(jiffies_str.at(i));
        total_jiffies += tmp;
        if(i < 4) { // The first three jiffies
            work_jiffies += tmp;
        }  
    }

    float work, total;
    work = work_jiffies - prev_work_jiffies;
    total = total_jiffies - prev_total_jiffies;
    unsigned int perc = work / total * 100;

    prev_total_jiffies = total_jiffies;
    prev_work_jiffies = work_jiffies;
    return "CPU: " + Common::make_bar(perc);
};
