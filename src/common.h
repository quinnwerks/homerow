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
#endif