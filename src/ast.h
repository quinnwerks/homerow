#ifndef AST_H
#define AST_H
#include "common.h"
#include "ast_node.h"

class Ast {
    public:
        Ast();
        ~Ast();
        Ast(Ast& copy_this) {
            *this = copy_this;
        }
        Ast& operator=(Ast& copy_this) {
            if(this != &copy_this) {
                m_curr_expr = copy_this.m_curr_expr;
                m_root = copy_this.m_root;
            }
            return *this;
        }

        // Interface to build the initial AST.
        void insert(AstNode& new_node) {m_curr_expr->insertChild(new_node);}
        void setCurrExpr(ExprNode& curr_expr) {m_curr_expr = &curr_expr;}
        ExprNode* getCurrExpr() const {return m_curr_expr;}
        ExprNode* getRoot() const {return m_root;}
        
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
};

#endif