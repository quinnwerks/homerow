#include "ast.h"

Ast::Ast() {
    ExprNode* m_root = new ExprNode(NODE_TYPE::PROG_START);
}

Ast::~Ast() {
    delete m_root;
}
