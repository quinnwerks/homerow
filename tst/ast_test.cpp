#include "gtest/gtest.h"
#include "ast.h"

TEST(AST_SHOULD, basic_ast_one_node) {
    Ast test_ast;
    std::cout << test_ast.get_debug_tree();

    std::string golden_tree("TYPE:2\n");
    ASSERT_EQ(golden_tree, test_ast.get_debug_tree());
}

TEST(AST_SHOULD, basic_ast_node_with_children) {
    Ast test_ast;
    BinaryNode* child_1 = new BinaryNode(NODE_TYPE::OPER_MUTE, 1, 2);
    ASSERT_TRUE(child_1);
    BinaryNode* child_2 = new BinaryNode(NODE_TYPE::IO, 3, 4);
    ASSERT_TRUE(child_2);

    test_ast.insert(*child_1);
    test_ast.insert(*child_2);

    std::string golden_tree("TYPE:2\n"
                            "  |-TYPE:4-REG:1-VAL:2\n"
                            "  `-TYPE:5-REG:3-VAL:4\n");
    ASSERT_EQ(golden_tree, test_ast.get_debug_tree());
}

TEST(AST_SHOULD, basic_ast_with_grandchildren) {
    Ast test_ast;
    BinaryNode* child_1 = new BinaryNode(NODE_TYPE::OPER_MUTE, 1, 2);
    ASSERT_TRUE(child_1);
    ExprNode* child_2 =  new ExprNode(NODE_TYPE::WHILE);
    ASSERT_TRUE(child_2);
    BinaryNode* child_3 = new BinaryNode(NODE_TYPE::IO, 1, 2);
    ASSERT_TRUE(child_3);
    test_ast.insert(*child_1);
    test_ast.insert(*child_2);
    test_ast.insert(*child_3);

    test_ast.setCurrExpr(*child_2);

    BinaryNode* grandchild_1 = new BinaryNode(NODE_TYPE::OPER_MOVE, 5, 6);
    BinaryNode* grandchild_2 = new BinaryNode(NODE_TYPE::OPER_MUTE, 5, 6);

    test_ast.insert(*grandchild_1);
    test_ast.insert(*grandchild_2);

    std::string golden_tree("TYPE:2\n"
                            "  |-TYPE:4-REG:1-VAL:2\n"
                            "  |-TYPE:6\n"
                            "  | |-TYPE:3-REG:5-VAL:6\n"
                            "  | `-TYPE:4-REG:5-VAL:6\n"
                            "  `-TYPE:5-REG:1-VAL:2\n");
    ASSERT_EQ(golden_tree, test_ast.get_debug_tree());
}