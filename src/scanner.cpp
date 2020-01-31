#include "scanner.h"
#include <assert.h>

Scanner::Scanner() {
    m_line = 0;
    m_col = 0;
}

Scanner::Scanner(Scanner& copy_this) {
    *this = copy_this;
}

Scanner& Scanner::operator=(const Scanner& copy_this) {
    if(this != &copy_this) {
        m_line = copy_this.m_line;
        m_col = copy_this.m_col;
    }
    return *this;
}

std::string Scanner::getNextWord(std::istream& input) {
    std::string lexeme;
    char c;
    // Clear any whitespace
    while(input.get(c) && isspace(c)) {
        if(c == '\n'){
            m_line++;
            m_col = 0;
        }
        else {
            m_col++;
        }
    }
    if (input.eof()) return lexeme;
    // Get next accepting state
    lexeme += c;
    while(input.get(c) && c == lexeme[lexeme.length()-1]){
        lexeme += c;
        m_col++;
    } 
    return lexeme;
}


