#include "../Project10/Lab2.h"
#include <gtest/gtest.h>
#include <limits.h>
TEST(CreateNode, Normal) {
    int key = 10;
    struct Node* node = createNode(key);
    ASSERT_NE(node, nullptr);
    ASSERT_EQ(node->data, key);
    ASSERT_EQ(node->color, RED);
    ASSERT_EQ(node->parent, nullptr);
    ASSERT_EQ(node->left, nullptr);
    ASSERT_EQ(node->right, nullptr);
    free(node);
}
TEST(CreateNode, Handlesame) {
    int key = 10;
    struct Node* node1 = createNode(key);
    struct Node* node2 = createNode(key);
    ASSERT_EQ(node1->data, node2->data);
    ASSERT_EQ(node1->color, node2->color);
    free(node1);
    free(node2);
}

TEST(CreateNode, Handlenotsame) {
    struct Node* node1 = createNode(10);
    struct Node* node2 = createNode(20);
    ASSERT_NE(node1->data, node2->data);
    free(node1);
    free(node2);
}

TEST(RBTreeTest, insertSingle) {
    struct Node* root = NULL;
    insertRBTree(&root, 1);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->data, 1);
    free(root);
}

TEST(RBTreeTest, insertMultiple) {
    struct Node* root = NULL;
    insertRBTree(&root, 1);
    insertRBTree(&root, 2);
    insertRBTree(&root, 0);
    ASSERT_EQ(root->data, 1);
    ASSERT_EQ(root->color, BLACK);
    ASSERT_EQ(root->left->data, 0);
    ASSERT_EQ(root->left->color, RED);
    ASSERT_EQ(root->right->data, 2);
    ASSERT_EQ(root->right->color, RED);
    free(root);
}

TEST(RBTreeTest, insert_exist) {
    struct Node* root = NULL;
    insertRBTree(&root, 1);
    insertRBTree(&root, 1);
    ASSERT_EQ(root->data, 1);
    ASSERT_EQ(root->color, BLACK);
    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->right, nullptr);
    free(root);

}
TEST(deletetest, DeleteFromEmpty) {
    struct Node* root = NULL;
    deleteNode(&root, 2);
    ASSERT_EQ(root, nullptr);
    free(root);
}

TEST(deletetest, Delete_node) {
    struct Node* root = NULL;
    insertRBTree(&root, 1);
    insertRBTree(&root, 2);
    insertRBTree(&root, 0);
    deleteNode(&root, 0);
    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->data, 1);
    ASSERT_EQ(root->color, BLACK);
    ASSERT_EQ(root->right->data, 2);
    ASSERT_EQ(root->right->color, RED);
    free(root);
}

TEST(deletetest, Delete_non_exist) {
    struct Node* root = NULL;
    insertRBTree(&root, 1);
    deleteNode(&root, 2);
    ASSERT_EQ(root->data, 1);
    ASSERT_EQ(root->color, BLACK);
    free(root);
}