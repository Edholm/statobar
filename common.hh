#ifndef __COMMON_H__
#define __COMMON_H__

#define COLOR_DEFAULT "#839496"
#define COLOR_CRIT "#c00000"
#define COLOR_WARN "#b58900"

class Common {
public:
    static std::string read_first_line(std::string);
    static std::string make_bar(int, int width = 10,
                                std::string tick_full = "▣",
                                std::string tick_empty = "▢");
};

#endif
