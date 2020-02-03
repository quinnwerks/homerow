#include <string>

#ifndef COMMON_H
#define COMMON_H
namespace LANG {
    enum TOKEN {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        IN,
        OUT,
        IF,
        WHILE,
        EXPR_BEGIN,
        EXPR_END,
        UNKNOWN,
        END_FILE
    };
}

using TOKEN_PAIR = std::pair<LANG::TOKEN, 
                             std::string>;
#endif