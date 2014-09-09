#ifndef __COMMON_H__
#define __COMMON_H__

class Common {
public:
    static std::string read_first_line(std::string);
    static std::string make_bar(int, int, std::string tick_full = "▣",
                         std::string tick_empty = "▢");
};

#endif
