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
    using STACK_OBJ = std::tuple<AstNode*, int, int, bool>;
    std::stack<STACK_OBJ> debug_stack;
    debug_stack.push({m_root, 0, 0, true});

    std::string debug_string;
    while(!debug_stack.empty()) {
        auto& tup = debug_stack.top();
        debug_stack.pop();
        AstNode* node;
        int level;
        int num_pipes;
        bool node_is_last;

        std::tie(node, level, num_pipes, node_is_last) = tup;
        assert(node);
        auto node_type = node->type();
        bool has_children = node_type == NODE_TYPE::WHILE ||
                            node_type == NODE_TYPE::PROG_START;
        if (has_children) {
            ExprNode* expr = static_cast<ExprNode*>(node);
            auto children = expr->children();
            int child_num_pipes = node_is_last ? num_pipes : num_pipes + 1;
            for(int i = children.size()-1; i >= 0; i--) {
                auto child = children[i];
                assert(child);
                bool child_is_last = i == children.size()-1;
                debug_stack.push({child, 
                                  level + 1, 
                                  child_num_pipes, 
                                  child_is_last});
            }
        }

        std::string node_string;
        for(int j = 0; j < level - num_pipes; j++) {
            node_string += "  ";
        }
        for(int i = 0; i < num_pipes; i++) {
            node_string += "| ";
        }

        node_string += node_is_last ? "`-" : "|-";
        node_string += std::to_string((int)node_type) + "\n";
        debug_string += node_string;
    }

    return debug_string;
}