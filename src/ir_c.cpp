#include "ir_c.h"

std::string IrToC::getOutput(const Ast& ast) {
    AstNode* p_root_node = ast.getRoot();
    assert(p_root_node);
    auto root_node = *p_root_node;
    return getOutput(root_node);
}

std::string IrToC::getOutput(const AstNode& node) {
    auto type = node.type();
    std::string node_output;
    
    if(type >= NODE_TYPE::PROG_START 
    && type <= NODE_TYPE::WHILE) {
        auto expr_node = AST_NODE_OP::cast<ExprNode>(node);
        node_output = getExprStringPair(expr_node);
    }
    else if (type > NODE_TYPE::WHILE 
    &&       type <= NODE_TYPE::IO) {
        auto binary_node = AST_NODE_OP::cast<BinaryNode>(node);
        node_output = getBinaryString(binary_node);
    }
    else {
        assert(false);
    }

    return node_output;
}

std::string IrToC::getExprStringPair(const ExprNode& node) {

}

std::string IrToC::getBinaryString(const BinaryNode& node) {

}