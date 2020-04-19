#include "parser.h"


/// @brief Boiler plate
Parser::Parser() {}
Parser::Parser(Parser& copy_this) {
    *this = copy_this;
}
Parser& Parser::operator=(Parser& copy_this) {
    if(this != &copy_this) {}
    return *this;    
}


/// @brief Entry point for parser
PARSER_RET_CODE Parser::parse_token(TOKEN_PAIR pair) {
    auto token = pair.first;
    switch(token) {
        case TOKEN::UP: break;
        case TOKEN::DOWN: break;
        case TOKEN::LEFT: break;
        case TOKEN::RIGHT: break;
        case TOKEN::IN: break;
        case TOKEN::OUT: break;
        case TOKEN::IF: break;
        case TOKEN::WHILE: break;
        case TOKEN::EXPR_BEGIN: break;
        case TOKEN::EXPR_END: break;
        case TOKEN::UNKNOWN: break;
        case TOKEN::END_FILE: break;
        default: break; 
    }

}