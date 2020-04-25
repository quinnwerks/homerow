#include "ast_node.h"

ExprNode::~ExprNode() {
    auto& children = m_children;
    auto child_begin = children.begin();
    auto chlid_end   = children.end();
    std::for_each(child_begin, chlid_end, [](AstNode* child) {
        assert(child);
        delete child;
    });  
    children.resize(0);
}

void ExprNode::visit() {
    auto& children = m_children;
    auto child_begin = children.begin();
    auto chlid_end   = children.end();
    std::for_each(child_begin, chlid_end, [](AstNode* child) {
        assert(child);
        child->visit();
    });
}

bool ExprNode::insertChild(AstNode& child) {
    m_children.emplace_back(&child);
}