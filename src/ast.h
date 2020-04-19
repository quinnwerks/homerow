#include "common.h"

enum class NODE_TYPE {
    OPER_MOVE,
    OPER_MUTE
};


class AstNode {
    public:
        AstNode(const NODE_TYPE type);
        AstNode(const AstNode& copy_this);

        int getCell();
        NODE_TYPE getType();
    protected:
        NODE_TYPE m_type;
        int m_cell;
};

class OperNode : AstNode {
    public:
        OperNode(int value);

        int getValue();

};