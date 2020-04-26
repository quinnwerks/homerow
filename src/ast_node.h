#ifndef AST_NODE_H
#define AST_NODE_H
#include "common.h"
#include <vector>
#include <string>


/// @brief An abstract syntax node. 
///        All node types are derived from this class. 
class AstNode {
    public:
        AstNode(const NODE_TYPE type) 
        : m_type(type) {}
        virtual ~AstNode() {}
        bool operator==(const AstNode& rhs) { return (*this).m_type 
                                              == rhs.m_type; }

        NODE_TYPE type() {return m_type;}

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
        virtual ~ExprNode() {delete_children();};
        void delete_children();

        void visit() override;

        void insertChild(AstNode& child);
        std::vector<AstNode*>& children(){ return m_children; }
    private:
        std::vector<AstNode*> m_children;
};

class BinaryNode : public AstNode {
    public:
        BinaryNode(const NODE_TYPE type, int reg, int val) 
        : AstNode(type), m_reg(reg), m_val(val) {}
        virtual ~BinaryNode() {}
        void visit() override;

        int reg() {return m_reg;}
        int val() {return m_val;}
    private:
        int m_reg;
        int m_val;
};


#endif