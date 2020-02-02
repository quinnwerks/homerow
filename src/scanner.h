#include <iostream>
#include <sstream>  
#include <unordered_map>

#include "frontend_enums.h"
class Scanner {
    public:
        using TOKEN_PAIR = std::pair<LANG::TOKEN, 
                                     std::string>;

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