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

PARSER_RET_CODE Parser::parse(Scanner& scanner) {
}

/// @brief Entry point for parser
PARSER_RET_CODE Parser::parse_token(Scanner& scanner, const TOKEN_PAIR& prev_token_pair) { 
    auto token_pair = scanner.getNextWord();
    auto token = token_pair.first;
    
    auto ret_code = PARSER_RET_CODE::FAIL;
    switch(token) {
        // PERFROM OP ON CURRENT CELL
        case TOKEN::UP: 
        case TOKEN::DOWN:  ret_code = parse_cell_mute(token_pair);
                           break;

        // CHANGE CELL
        case TOKEN::LEFT:
        case TOKEN::RIGHT: ret_code = parse_cell_move(token_pair);
                           break;
        
        // OUTPUT CELL
        case TOKEN::IN:    
        case TOKEN::OUT:   ret_code = parse_cell_ioop(token_pair);
                           break;
        
        // FLOW CONTROL
        case TOKEN::WHILE: ret_code = parse_flow_while(scanner, token_pair);
                           break;

        case TOKEN::EXPR_END: ret_code = PARSER_RET_CODE::CHECK_EXPR_END;
                              break;

        // EOF
        case TOKEN::END_PROG: ret_code = PARSER_RET_CODE::CHECK_EOF;
                              break;
        default: break; 
    }

    return ret_code;
}

/// @brief Create an increment or decrement node
PARSER_RET_CODE Parser::parse_cell_mute(const TOKEN_PAIR& token_pair) {
    auto token = token_pair.first;
    int value = token == TOKEN::UP ? 1 : -1;
    return PARSER_RET_CODE::CONTINUE_MUTE;
}

/// @brief Move up a cell or down a cell. If the cell does not exist
///        create one.
PARSER_RET_CODE Parser::parse_cell_move(const TOKEN_PAIR& token_pair) {
    auto token = token_pair.first;
    int value = token == TOKEN::RIGHT ? 1 : -1;
    return PARSER_RET_CODE::CONTINUE_MOVE;
}

PARSER_RET_CODE Parser::parse_cell_ioop(const TOKEN_PAIR& token_pair) {

    return PARSER_RET_CODE::CONTINUE_IOOP;
}

PARSER_RET_CODE Parser::parse_flow_while(Scanner& scanner, const TOKEN_PAIR& token_pair) {
    auto ret_code = PARSER_RET_CODE::FAIL;
    auto expr_token = scanner.getNextWord().first;
    if(expr_token != TOKEN::EXPR_BEGIN) {
        return PARSER_RET_CODE::FAIL_NO_EXPR_BEGIN;
    }

    while(ret_code != PARSER_RET_CODE::CHECK_EXPR_END) {
        ret_code = parse_token(scanner, token_pair);
        ret_code = ret_code == PARSER_RET_CODE::CHECK_EOF ?
                   PARSER_RET_CODE::FAIL_EARLY_EOF : ret_code;

        if(ret_code >= PARSER_RET_CODE::FAIL_UNEXPECTED_SYMBOL 
        && ret_code <= PARSER_RET_CODE::FAIL) {
            return ret_code;
        }
    }

    return PARSER_RET_CODE::CONTINUE_WHILE;
}