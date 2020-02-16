#include "parser.h"

Parser::Parser() {

}

Parser::Parser(Parser& copy_this) {
    *this = copy_this;
}

Parser& Parser::operator=(Parser& copy_this) {
    if(this != &copy_this) {

    }
    return *this;    
}

PARSER_RET_CODE Parser::validExpr(TOKEN_PAIR word) {
    return false;
}

std::string Parser::dumpRepresentation() {
    return "";
}


// This determines if a sentence is valid
// If a control statement is detected validity
// will be determined from the top down
// Things to build: -> AST
//                  -> CFG

// Words -> Sentences as AST
// AST -> CALL Graph
Parser::PARSER_RET_CODE dummy_func(TOKEN_PAIR pair) {
    auto token = pair.first;
    if(token == LANG::TOKEN::END_FILE) {
        return ACCEPT;
    }
    if(token == LANG::TOKEN::WHILE || token == LANG::TOKEN::IF) {
        //TODO: Mutual recursion???
    }
    else if (token == LANG::TOKEN::EXPR_BEGIN || token == LANG::EXPR_END) {
        return FAIL;
    }
    else if (token == LANG::TOKEN::UNKNOWN){
        return FAIL;
    }
    else {
        return dummy_func(getNextPair)
    }

}

Parser::PARSER_RET_CODE while_dummy_func(TOKEN_PAIR pair) {
    auto token = pair.first;
    if(token == LANG::TOKEN::EXPR_BEGIN) {

    }
}