/* Formates date/time
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <stdlib.h>
#include <ctime>
#include <map>
#include "common.hh"
#include "vpn.hh"

#include <iostream>

using namespace std;

bool VPN::vpn_enabled() {
    return system("pgrep openvpn >/dev/null") == 0;
}

string VPN::generate_json() {
    map<string, string> m;

    if(vpn_enabled())
    {
        m["full_text"] = " \uf023 VPN on ";
        m["color"] = COLOR_WARN;
    } else {
        m["full_text"] = "";
        m["separator"] = "false";
    }
    return Common::map_to_json(m);
}
