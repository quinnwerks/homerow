#ifndef AST_H
#define AST_H
#include "common.h"
#include "ast_node.h"

class Ast {
    public:
        Ast();
        ~Ast();
    private:
        ExprNode* m_root;
};

#endif