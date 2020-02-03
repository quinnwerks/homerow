#include "common.h"

#include <iostream>
#include <sstream>  
#include <unordered_map>

#ifndef SCANNER_H
#define SCANNER_H
class Scanner {
    public:
        Scanner();
        Scanner(Scanner& copy_this);
        Scanner& operator=(const Scanner& copy_this);
        TOKEN_PAIR getNextWord(std::istream& input);
            
    private:
        void setup_table();

        unsigned int m_line;  
        unsigned int m_col;
        std::unordered_map<std::string, LANG::TOKEN> m_table;
};
#endif