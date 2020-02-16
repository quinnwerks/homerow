#include "common.h"
#include "scanner.h"

#ifndef PARSER_H
#define PARSER_H
class Parser {
    public:
        enum PARSER_RET_CODE {
            ACCEPT,
            FAIL
        };
        Parser();
        Parser(Parser& copy_this);
        Parser& operator=(Parser & copy_this);


        PARSER_RET_CODE validExpr(TOKEN_PAIR word);
        std::string dumpRepresentation();   
        
    private:
        Scanner m_scanner;
};
#endif
