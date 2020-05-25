#include "gtest/gtest.h"
#include "ast_node.h"

TEST(AST_NODE_SHOULD, node_no_children) {
    // test_node
    //     |
    //     * 
    ExprNode* test_node = new ExprNode(NODE_TYPE::PROG_START);
    ASSERT_EQ(0, test_node->children().size());
    delete test_node;
}

TEST(AST_NODE_SHOULD, node_with_leaf) {
    // test_node
    // `- test_leaf
    ExprNode* test_node = new ExprNode(NODE_TYPE::WHILE);
    ASSERT_TRUE(test_node);

    ExprNode* test_leaf = new ExprNode(NODE_TYPE::IO);
    ASSERT_TRUE(test_leaf);

    test_node->insertChild(*test_leaf);
    ASSERT_EQ(1, test_node->children().size());
    ASSERT_EQ(test_leaf, test_node->children()[0]);
    test_node->delete_children();
    ASSERT_EQ(0, test_node->children().size());
    delete test_node;
}

TEST(AST_NODE_SHOULD, test_node_with_grandchildren) {
    // test_node
    // `- test_child
    //    `- test_grandchild
    ExprNode* test_node       = new ExprNode(NODE_TYPE::WHILE);
    ASSERT_TRUE(test_node);

    ExprNode* test_child      = new ExprNode(NODE_TYPE::WHILE);
    ASSERT_TRUE(test_child); 

    ExprNode* test_grandchild = new ExprNode(NODE_TYPE::IO);
    ASSERT_TRUE(test_grandchild); 

    test_node->insertChild(*test_child);
    test_child->insertChild(*test_grandchild);
    ASSERT_EQ(1, test_node->children().size());
    ASSERT_EQ(1, test_child->children().size());
    ASSERT_EQ(0, test_grandchild->children().size());

    // This test is good a good way 
    // to check that the destructor works
    delete test_node;
}

TEST(AST_NODE_SHOULD, node_with_several_leaves) {
    // test_node
    // |- Move(0,4)
    // |- Mute(1,5)
    // `- io  (2,6)
    ExprNode* test_node = new ExprNode(NODE_TYPE::PROG_START);
    ASSERT_TRUE(test_node);

    std::vector<BinaryNode*> test_leaves;
    test_leaves.emplace_back(new BinaryNode(NODE_TYPE::OPER_MOVE, 0, 4));
    test_leaves.emplace_back(new BinaryNode(NODE_TYPE::OPER_MUTE, 1, 5));
    test_leaves.emplace_back(new BinaryNode(NODE_TYPE::IO,        2, 6));
    ASSERT_TRUE(test_leaves[0]);
    ASSERT_TRUE(test_leaves[1]);
    ASSERT_TRUE(test_leaves[2]);

    test_node->insertChild(*test_leaves[0]);
    test_node->insertChild(*test_leaves[1]);
    test_node->insertChild(*test_leaves[2]);
    
    auto children = test_node->children();
    ASSERT_EQ(3, children.size());
    for(int i = 0; i < children.size(); i++) {
        BinaryNode* child = static_cast<BinaryNode*>(children[i]);
        ASSERT_EQ(test_leaves[i], child);
        ASSERT_EQ(test_leaves[i]->type(), child->type());
        ASSERT_EQ(test_leaves[i]->reg(),  child->reg());
        ASSERT_EQ(test_leaves[i]->val(),  child->val());
    }
    test_node->delete_children();
    ASSERT_EQ(0, test_node->children().size());
    delete test_node;
}