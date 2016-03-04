/* Get essid and signal strength from wifi
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
*/
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <iwlib.h>
#include "network.hh"
#include "common.hh"

using namespace std;

Network::winfo Network::collect() {
    struct winfo wi;
    int skfd;
    struct wireless_info *winfo;
    winfo = (struct wireless_info*)malloc(sizeof(struct wireless_info));
    memset(winfo, 0, sizeof(struct wireless_info));

    skfd = iw_sockets_open();
    if(iw_get_basic_config(skfd, INTERFACE, &(winfo->b)) > -1) {
        // Get statistics, such as quality
        if (iw_get_stats(skfd, INTERFACE, &(winfo->stats),
                &winfo->range, winfo->has_range) >= 0) {
            winfo->has_stats = 1;
        }
        if (iw_get_range_info(skfd, INTERFACE, &(winfo->range)) >= 0) {
            winfo->has_range = 1;
        }
        wi.quality = (winfo->stats.qual.qual*100) /
                        winfo->range.max_qual.qual;
        wi.level = winfo->stats.qual.level;

        if (winfo->b.has_essid) {
            if (winfo->b.essid_on) {
                wi.essid = winfo->b.essid;
                wi.is_connected = true;
            }
            else {
                wi.essid = "N/A";
                wi.is_connected = false;
            }
        }
    }
    iw_sockets_close(skfd);
    free(winfo);
    return wi;
}

string Network::generate_json() {
    struct winfo wi = collect();
    map<string, string> m;
    if(wi.is_connected) {
        string filler = Common::filler_json("  " + wi.essid + " ") + ", ";
        string color;
        if(wi.quality <= 20) {
            color = COLOR_WARN;
        } else if(wi.quality < 90) {
            color = COLOR_DEFAULT;
        } else {
            color = COLOR_GOOD;
        }

        m["full_text"] ="(" + to_string(wi.level) + " dBm) ";
        m["color"] = color;
        return filler + Common::map_to_json(m);
    } else {
        // List any connected wired interfaces.
        ifaddrs *ifap;
        if(getifaddrs(&ifap) < 0) {
            // fuqit, we're outta here
            return "";
        }
        for(ifaddrs*it = ifap; it->ifa_next != NULL; it=it->ifa_next) {
            if (it->ifa_addr == NULL || it->ifa_addr->sa_family != AF_INET) {
                // We only care about ipv4 interfaces for now...
                continue;
            }
            if(strcmp(it->ifa_name, INTERFACE) == 0 ||
                    strcmp(it->ifa_name, "lo") == 0) {
                // Ignore loopback and our wifi interface
                 continue;
            }
            sockaddr_in* ipv4_addr = (sockaddr_in*)it->ifa_addr;
            char *ipaddr = inet_ntoa(ipv4_addr->sin_addr);
            m["full_text"] = " " + string(it->ifa_name) + " (" + ipaddr + ") ";
            // Quit after first match...
            freeifaddrs(ifap);
            return Common::map_to_json(m);
        }
        return "";
    }
};
