#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stack>
#include <iostream>
#include <tuple>

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
        END_PROG,
        UNKNOWN
    };
}
using TOKEN = LANG::TOKEN;

/*
 * EXPR ::= OP
 * OP ::= UP | DOWN | LEFT | RIGHT | IN | OUT | CNTRL
 * CNTRL = (IF | WHILE) EXPR_BEGIN OPS EXPR_END
 * 
 */

using TOKEN_PAIR = std::pair<LANG::TOKEN, 
                             std::string>;

namespace TYPE_ENUM {
    enum class NODE_TYPE {
        // Types used in production
        PROG_START,
        WHILE,
        OPER_MOVE,
        OPER_MUTE,
        IO
    };
}
using NODE_TYPE = TYPE_ENUM::NODE_TYPE;

#endif