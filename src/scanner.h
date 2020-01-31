#include <iostream>
#include <sstream>  
class Scanner {
    public:
        Scanner();
        Scanner(Scanner& copy_this);
        Scanner& operator=(const Scanner& copy_this);
        std::string getNextWord(std::istream& input);
            
    private:
        unsigned int m_line;  
        unsigned int m_col;
};