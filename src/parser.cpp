#include "parser.h"


/// @brief Boiler plate
Parser::Parser() {
    // Start at cell zero
    m_parser_state.curr_cell = 0;
}

Parser::Parser(const Parser& copy_this) {
    *this = copy_this;
}
Parser Parser::operator=(const Parser& copy_this) {
    if(this != &copy_this) {}
    return *this;    
}

ParserState Parser::getState() {
    return m_parser_state;
}

PARSER_RET_CODE Parser::parse(Scanner& scanner) {
    auto ret_code = PARSER_RET_CODE::FAIL;
    while(ret_code != PARSER_RET_CODE::CHECK_EOF) {
        ret_code = parse_token(scanner);
        if(ret_code >= PARSER_RET_CODE::FAIL_UNEXPECTED_SYMBOL 
        && ret_code <= PARSER_RET_CODE::FAIL) {
            return PARSER_RET_CODE::FAIL;
        }
    }
    return PARSER_RET_CODE::ACCEPT;
}

/// @brief Entry point for parser
PARSER_RET_CODE Parser::parse_token(Scanner& scanner) { 
    auto token_pair = scanner.getNextWord();
    auto token = token_pair.first;
    
    auto ret_code = PARSER_RET_CODE::FAIL;
    switch(token) {
        // PERFROM OP ON CURRENT CELL
        case TOKEN::UP: 
        case TOKEN::DOWN:     ret_code = parse_cell_mute(token_pair);
                              break;

        // CHANGE CELL
        case TOKEN::LEFT:
        case TOKEN::RIGHT:    ret_code = parse_cell_move(token_pair);
                              break;
        
        // OUTPUT CELL
        case TOKEN::IN:    
        case TOKEN::OUT:      ret_code = parse_cell_ioop(token_pair);
                              break;
        
        // FLOW CONTROL
        case TOKEN::WHILE:    ret_code = parse_flow_while(scanner, 
                                                          token_pair);
                              break;

        case TOKEN::EXPR_END: ret_code = PARSER_RET_CODE::CHECK_EXPR_END;
                              break;

        // EOF
        case TOKEN::END_PROG: ret_code = PARSER_RET_CODE::CHECK_EOF;
                              break;
        
        default:              ret_code = PARSER_RET_CODE::FAIL_UNEXPECTED_SYMBOL; 
                              break; 
    }
    return ret_code;
}

/// @brief Create an increment or decrement node
PARSER_RET_CODE Parser::parse_cell_mute(const TOKEN_PAIR& token_pair) {
    auto token = token_pair.first;
    int curr_cell = m_parser_state.curr_cell;
    int value = token == TOKEN::UP ? 1 : -1;

    auto new_node = new BinaryNode(NODE_TYPE::OPER_MUTE, 
                                   curr_cell, 
                                   value);
    assert(new_node);
    m_ast.insert(*new_node);
    return PARSER_RET_CODE::CONTINUE_MUTE;
}

/// @brief Move up a cell or down a cell. If the cell does not exist
///        create one.
PARSER_RET_CODE Parser::parse_cell_move(const TOKEN_PAIR& token_pair) {
    auto token = token_pair.first;
    int value = token == TOKEN::RIGHT ? 1 : -1;

    m_parser_state.curr_cell = m_parser_state.curr_cell + value;
    int curr_cell = m_parser_state.curr_cell;

    auto new_node = new BinaryNode(NODE_TYPE::OPER_MOVE, 
                                   curr_cell, 
                                   value);
    assert(new_node);
    m_ast.insert(*new_node);
    return PARSER_RET_CODE::CONTINUE_MOVE;
}

PARSER_RET_CODE Parser::parse_cell_ioop(const TOKEN_PAIR& token_pair) {
    int curr_cell = m_parser_state.curr_cell;
    auto new_node = new BinaryNode(NODE_TYPE::IO, curr_cell, 0);
    assert(new_node);
    m_ast.insert(*new_node);
    return PARSER_RET_CODE::CONTINUE_IOOP;
}

PARSER_RET_CODE Parser::parse_flow_while(Scanner& scanner, const TOKEN_PAIR& token_pair) {
    auto ret_code = PARSER_RET_CODE::FAIL;
    auto expr_token = scanner.getNextWord().first;
    if(expr_token != TOKEN::EXPR_BEGIN) {
        return PARSER_RET_CODE::FAIL_NO_EXPR_BEGIN;
    }

    auto new_node = new ExprNode(NODE_TYPE::WHILE);
    assert(new_node);
    m_ast.insert(*new_node);
    ExprNode* prev_expr = m_ast.getCurrExpr();
    m_ast.setCurrExpr(*new_node);

    while(ret_code != PARSER_RET_CODE::CHECK_EXPR_END) {
        ret_code = parse_token(scanner);
        ret_code = ret_code == PARSER_RET_CODE::CHECK_EOF ?
                   PARSER_RET_CODE::FAIL_EARLY_EOF : ret_code;

        if(ret_code >= PARSER_RET_CODE::FAIL_UNEXPECTED_SYMBOL 
        && ret_code <= PARSER_RET_CODE::FAIL) {
            return ret_code;
        }
    }

    m_ast.setCurrExpr(*prev_expr);

    return PARSER_RET_CODE::CONTINUE_WHILE;
}