#ifndef AST_NODE_H
#define AST_NODE_H
#include "common.h"
#include <vector>


/// @brief An abstract syntax node. 
///        All node types are derived from this class. 
class AstNode {
    public:
        AstNode(const NODE_TYPE type) 
        : m_type(type) {}        
        bool operator==(const AstNode& rhs) { return (*this).m_type 
                                              == rhs.m_type; }

        NODE_TYPE get_type() {return m_type;}

        virtual void visit() = 0;
    private:
        NODE_TYPE m_type;
};

/// @brief Expr nodes are the inner nodes of the AST. 
///        They can have an arbitrary number of children.
class ExprNode : public AstNode {
    public:
        ExprNode(const NODE_TYPE type) 
        : AstNode(type) {}       
        ExprNode(const ExprNode& copy_this);
        ~ExprNode();

        void visit() override;
        bool insertChild(AstNode& child);
    private:
        std::vector<AstNode*> m_children;
};

class BinaryNode : public AstNode {
    BinaryNode(const NODE_TYPE type) 
    : AstNode(type) {}
};


#endif