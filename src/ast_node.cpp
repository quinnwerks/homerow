#include "ast_node.h"

ExprNode::ExprNode(const ExprNode& copy_this) : AstNode(copy_this) {
    *this = copy_this;
}

std::string ExprNode::getDebugString() const {
    std::string debug_string = AstNode::getDebugString();
    return debug_string;
}

ExprNode ExprNode::operator=(const ExprNode& copy_this) {
    if(this != &copy_this) {
        this->m_children = copy_this.m_children;
    }
    return *this;
}

void ExprNode::delete_children() {
    auto& children = m_children;
    auto child_begin = children.begin();
    auto chlid_end   = children.end();
    std::for_each(child_begin, chlid_end, [](AstNode* child) {
        assert(child);
        delete child;
    });  
    children.resize(0);
}

void ExprNode::insertChild(AstNode& child) {
    m_children.emplace_back(&child);
}

BinaryNode::BinaryNode(const BinaryNode& copy_this) : AstNode(copy_this) {
    *this = copy_this;
}

std::string BinaryNode::getDebugString() const {
    std::string debug_string = AstNode::getDebugString() 
                             + "-REG:" + std::to_string(m_reg)
                             + "-VAL:"  + std::to_string(m_val);
    return debug_string;
}

BinaryNode BinaryNode::operator=(const BinaryNode& copy_this) {
    if(this != &copy_this) {
        this->m_reg = copy_this.m_reg;
        this->m_val = copy_this.m_val;
    }
    return *this;
}
