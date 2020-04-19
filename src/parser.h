#include "common.h"
#include "scanner.h"

#ifndef PARSER_H
#define PARSER_H
enum class PARSER_RET_CODE {
    CONTINUE_MUTE,
    CONTINUE_MOVE,
    CONTINUE_IOOP,
    CONTINUE_WHILE,
    CHECK_EXPR_END,
    CHECK_EOF,
    FAIL_UNEXPECTED_SYMBOL,
    FAIL_EARLY_EOF,
    FAIL_NO_EXPR_BEGIN,
    FAIL
};

class Parser {
    public:

        Parser();
        Parser(Parser& copy_this);
        Parser& operator=(Parser & copy_this);

        PARSER_RET_CODE parse(Scanner& scanner);
        PARSER_RET_CODE parse_token(Scanner& scanner, const TOKEN_PAIR& prev_token_pair);
       
    private:
        PARSER_RET_CODE parse_cell_mute(const TOKEN_PAIR& token_pair);
        PARSER_RET_CODE parse_cell_move(const TOKEN_PAIR& token_pair);
        PARSER_RET_CODE parse_cell_ioop(const TOKEN_PAIR& token_pair);

        PARSER_RET_CODE parse_flow_while(Scanner& scanner, const TOKEN_PAIR& prev_token_pair);
        PARSER_RET_CODE validExpr(TOKEN_PAIR word);
        std::string dumpRepresentation();   
};
#endif
