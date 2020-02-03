#include "common.h"

#ifndef PARSER_H
#define PARSER_H
class Parser {
    public:
        Parser();
        Parser(Parser& copy_this);
        Parser& operator=(Parser & copy_this);

        bool processWord(TOKEN_PAIR word);
        std::string dumpRepresentation();    
};
#endif