/* Retrieve CPU usage statistics.
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
*/

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include "cpu.hh"
#include "common.hh"

using namespace std;
using namespace boost;

unsigned int CPU::calc_usage() {
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
    prev_total_jiffies = total_jiffies;
    prev_work_jiffies = work_jiffies;

    return work / total * 100;
}

string CPU::generate_json() {
    unsigned int usage = calc_usage();
    string filler = Common::filler_json("  CPU ");
    string color;
    if(usage >= 70) {
        color = COLOR_CRIT;
    } else if(usage >= 45) {
        color = COLOR_WARN;
    } else {
        color = COLOR_DEFAULT;
    }

    if(usage <= 15) {
        return "";
    }

    map<string, string> m;
    m["full_text"] = Common::make_bar(usage) + " ";
    m["color"] = color;

    return filler + ", " + Common::map_to_json(m);
};
