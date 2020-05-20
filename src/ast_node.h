#ifndef AST_NODE_H
#define AST_NODE_H
#include "common.h"
#include <vector>
#include <string>


/// @brief An abstract syntax node. 
///        All node types are derived from this class. 
class AstNode {
    public:
        AstNode(const NODE_TYPE type) : m_type(type) {}
        AstNode(const AstNode& copy_this) {this->m_type = copy_this.m_type;};
        virtual ~AstNode() {}
        virtual std::string getDebugString() { 
            return "TYPE:" + std::to_string((int)this->m_type);
        }
        
        NODE_TYPE type() {return m_type;}
    private:
        NODE_TYPE m_type;
};

/// @brief Expr nodes are the inner nodes of the AST. 
///        They can have an arbitrary number of children.
class ExprNode : public AstNode {
    public:
        ExprNode(const NODE_TYPE type) : AstNode(type) {}
        ExprNode(const ExprNode& copy_this);
        ExprNode operator=(const ExprNode& copy_this);      
        virtual ~ExprNode() {delete_children();};
        std::string getDebugString() override;

        void delete_children();
        void insertChild(AstNode& child);
        std::vector<AstNode*>& children(){ return m_children; }
    private:
        std::vector<AstNode*> m_children;
};

class BinaryNode : public AstNode {
    public:
        BinaryNode(const NODE_TYPE type, int reg, int val) : AstNode(type), m_reg(reg), m_val(val) {}
        BinaryNode(const BinaryNode& copy_this);
        BinaryNode operator=(const BinaryNode& copy_this);       
        virtual ~BinaryNode() {}
        std::string getDebugString() override;

        int reg() {return m_reg;}
        int val() {return m_val;}
    private:
        int m_reg;
        int m_val;
};


#endif