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
PARSER_RET_CODE Parser::parse_token(const TOKEN_PAIR& token_pair) {
    auto ret_code = PARSER_RET_CODE::FAIL;
    auto token = token_pair.first;
    switch(token) {
        // PERFROM OP ON CURRENT CELL
        case TOKEN::UP: 
        case TOKEN::DOWN:  ret_code = parse_cell_oper(token_pair);
                           break;

        // CHANGE CELL
        case TOKEN::LEFT:
        case TOKEN::RIGHT: ret_code = parse_cell_move(token_pair);
                           break;
        
        // OUTPUT CELL
        case TOKEN::IN: 
        case TOKEN::OUT: break;
        
        // FLOW CONTROL
        case TOKEN::IF: 
        case TOKEN::WHILE: 

        // OTHER...
        case TOKEN::EXPR_BEGIN: break;
        case TOKEN::EXPR_END: break;

        // EOF
        case TOKEN::END_FILE: break;
        default: break; 
    }
    
    return ret_code;
}

/// @brief Create an increment or decrement node
PARSER_RET_CODE Parser::parse_cell_oper(const TOKEN_PAIR& token_pair) {
    return PARSER_RET_CODE::CONTINUE_OPER;
}

/// @brief Move up a cell or down a cell. If the cell does not exist
///        create one.
PARSER_RET_CODE Parser::parse_cell_move(const TOKEN_PAIR& token_pair) {
    return PARSER_RET_CODE::CONTINUE_MOVE;
}