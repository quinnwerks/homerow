#ifndef AST_H
#define AST_H
#include "common.h"

enum class NODE_TYPE {
    OPER_MOVE,
    OPER_MUTE
};


class AstNode {
    public:
        AstNode(const NODE_TYPE type, const int cell) 
        : m_type(type), m_cell(cell) {}
        
        AstNode(const AstNode& copy_this);

        int getCell();
        NODE_TYPE getType();
    protected:
        NODE_TYPE m_type;
        int m_cell;
};

class OperNode : AstNode {
    public:
        OperNode(const NODE_TYPE type, const int cell, const int value) 
        : m_value(value), AstNode(type, cell) {}

        int getValue();
    protected:
        int m_value;
};

#endif