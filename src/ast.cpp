#include "ast.h"

Ast::Ast() {
    m_root = new ExprNode(NODE_TYPE::PROG_START);
    assert(m_root);
    m_curr_expr = m_root;
}

Ast::~Ast() {
    if(m_root) {
        delete m_root;
        m_root = nullptr;
    }
}

std::string Ast::get_debug_tree() {
    assert(m_root);
    return get_debug_tree(*m_root, 0);
}

std::string Ast::get_debug_tree(ExprNode& node, const int level) {
    auto get_preamble = [] (int level, const std::string& final_part) {
        std::string preamble;
        for(int i = 0; i < level - 1; i++) {
            
            preamble += "| ";
        }
        preamble += final_part;
        return preamble;
    };

    std::string debug_string;
    
    debug_string += std::to_string((int) node.type()) + "\n";

    auto children = node.children();
    for(int i = 0; i < children.size(); i++) {
        auto child = children[i];
        assert(child);
        std::string final_part = i != children.size() -1 ? "|-" : "`-";
        std::string child_string = get_preamble(level + 1, final_part);
        
        if(child->type() == NODE_TYPE::WHILE) {
            auto expr_child = static_cast<ExprNode*>(child); 
            assert(expr_child);
            child_string += get_debug_tree(*expr_child, level+1);
        }
        else {
            child_string += std::to_string((int) child->type()) + "\n";
        }

        debug_string += child_string;
    }
    return debug_string;
}
