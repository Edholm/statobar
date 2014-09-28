#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#include <map>

#define COLOR_DEFAULT "#839496"
#define COLOR_CRIT "#c00000"
#define COLOR_WARN "#b58900"
#define COLOR_GOOD "#00c000"

class Common {
public:
    static std::string read_first_line(std::string);
    static std::string make_bar(int, int width = 10,
                                std::string tick_full = "▣",
                                std::string tick_empty = "▢");
    static std::string map_to_json(std::map<std::string, std::string>);
    static std::string filler_json(std::string full_text,
                                   std::string color = COLOR_DEFAULT);
};

#endif
