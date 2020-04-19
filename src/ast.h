#ifndef AST_H
#define AST_H
#include "common.h"
#include <vector>

class Ast {
    public:
        Ast();
        bool insert(AstNode& new_node);
    private:
        //ExprNode m_root(NODE_TYPE::BODY);
        //AstNode& m_curr_node;
};

/// @brief An abstract syntax node. All node types are derived from this class. 
class AstNode {
    public:
        AstNode(const NODE_TYPE type) : m_type(type) {}        
        AstNode(const AstNode& copy_this);
        bool operator==(const AstNode& rhs) {return (*this).m_type == rhs.m_type;}
        bool operator=(const AstNode& copy_this);

        virtual void visit() = 0;
    private:
        NODE_TYPE m_type;
};

/// @brief Expr nodes are the inner nodes of the AST. 
///        They can have an arbitrary number of children.
class ExprNode : public AstNode {
    public:
        ExprNode(const NODE_TYPE type) : AstNode(type) {}       
        ExprNode(const ExprNode& copy_this);
        bool operator==(const AstNode& rhs);
        bool operator=(const AstNode& rhs);

        void visit() override;
        void insert();
    private:
        std::vector<AstNode> children;
};

#endif