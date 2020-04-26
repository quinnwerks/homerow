#ifndef AST_H
#define AST_H
#include "common.h"
#include "ast_node.h"

class Ast {
    public:
        Ast();
        ~Ast();

        // Interface to build the initial AST.
        void insert(AstNode& new_node) {m_curr_expr->insertChild(new_node);}
        void setCurrExpr(ExprNode& curr_expr) {m_curr_expr = &curr_expr;}
        ExprNode& getCurrExpr() {return *m_curr_expr;}
        
        std::string get_debug_tree();

        //TODO: this should be done later
        class iterator {
            public:  
                iterator(AstNode* ptr) : m_ptr(ptr) {}
                bool operator==(const iterator& rhs) {return m_ptr == rhs.m_ptr; };
                bool operator!=(const iterator& rhs) {return m_ptr != rhs.m_ptr; };

                iterator operator++();
                iterator operator--();
                iterator operator++(int junk);
                iterator operator--(int junk);
                AstNode& operator*();
                AstNode* operator->();
            
            private:
                AstNode* m_ptr;
        };

    private:
        ExprNode* m_root = nullptr;
        ExprNode* m_curr_expr = nullptr;
        // Useful for debugging
        std::string get_debug_tree(ExprNode& node, const int level);
};

#endif