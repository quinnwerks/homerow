#ifndef IR_C_H
#define IR_C_H
#include "common.h"
#include "ast_node.h"
#include "ast.h"

class IrToC {
    public:
        std::string getOutput(const Ast& ast);
    private:
        std::string getOutput(const AstNode& node);
        std::string getNodeString(const AstNode& node);
        std::string getExprStringPair(const ExprNode& node);
        std::string getBinaryString(const BinaryNode& node);
};

#endif