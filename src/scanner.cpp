#include "scanner.h"

Scanner::Scanner(std::istream& stream) : m_stream(&stream) {
    m_line = 0;
    m_col = 0;
    setup_table();
}

Scanner::Scanner(Scanner& copy_this) {
    *this = copy_this;
}

Scanner Scanner::operator=(const Scanner& copy_this) {
    if(this != &copy_this) {
        m_line = copy_this.m_line;
        m_col = copy_this.m_col;
        m_table = copy_this.m_table;
        m_stream = copy_this.m_stream;
    }
    return *this;
}

void Scanner::set_istream(std::istream& stream) {
    m_stream = &stream;
}

std::istream& Scanner::get_istream() {
    return *m_stream;
}

void Scanner::setup_table() {
    m_table["k"] = LANG::TOKEN::UP;
    m_table["j"] = LANG::TOKEN::DOWN;
    m_table["h"] = LANG::TOKEN::LEFT;
    m_table["l"] = LANG::TOKEN::RIGHT;
    m_table["a"] = LANG::TOKEN::IN;
    m_table["s"] = LANG::TOKEN::OUT;
    m_table["G"] = LANG::TOKEN::IF;
    m_table["F"] = LANG::TOKEN::WHILE;
    m_table["H"] = LANG::TOKEN::EXPR_BEGIN;
    m_table["h"] = LANG::TOKEN::EXPR_END;
    m_table[""]  = LANG::TOKEN::END_PROG;
}

TOKEN_PAIR Scanner::getNextWord() {
    return getNextWord(*m_stream);
}

TOKEN_PAIR Scanner::getNextWord(std::istream& input) {
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
    if (input.eof()) return std::make_pair(LANG::TOKEN::END_PROG, lexeme);
    // Get next accepting state
    lexeme += c;
    m_col++;
    // For now language spec is simple enough just to do this:
    if(m_table.find(lexeme) == m_table.end()) {
        return std::make_pair(LANG::TOKEN::UNKNOWN, lexeme);
    }
    else {
        return std::make_pair(m_table[lexeme], lexeme);
    }
    // TODO: number support would be nice but might not work with grammar
}
