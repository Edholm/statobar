/*
 * Copyright 2016 Johan 'Horv' Andersson <drhorv@gmail.com>
 */

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include "packages-to-update.hh"
#include "common.hh"
#include <string>
#include <iostream>

using namespace std;
using namespace boost;

#define PACKAGE_ICON "\uf187"

string PackagesToUpdate::exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
};

unsigned int PackagesToUpdate::get_nbr_pacman_packages() {
  string output = boost::trim_copy(exec("checkupdates | wc -l"));
  return lexical_cast<unsigned int>(output);
};

string PackagesToUpdate::generate_json() {
    unsigned int packages = get_nbr_pacman_packages();
    if(packages == 0) {
      return "";
    }

    string color;
    if(packages >= 25) {
        color = COLOR_CRIT;
    } else if(packages >= 10) {
        color = COLOR_WARN;
    } else {
        color = COLOR_DEFAULT;
    }

    string status = PACKAGE_ICON;

    map<string, string> m;
    m["full_text"] = status + "  " + std::to_string(packages);
    m["color"] = color;

    return Common::map_to_json(m);
};
