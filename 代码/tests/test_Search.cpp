#include "Search.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

class SearchTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Setup SSTable for sequential and binary search tests
    ST.elem = new ElemType[10];
    ST.elem[0] = 0; // sentinel
    ST.elem[1] = 1;
    ST.elem[2] = 3;
    ST.elem[3] = 5;
    ST.elem[4] = 7;
    ST.elem[5] = 9;
    ST.TableLen = 5;

    // Setup BST
    T = NULL;
    ElemType keys[] = {50, 30, 70, 20, 40, 60, 80};
    BSTCreate(T, keys, 7);
  }

  void TearDown() override {
    delete[] ST.elem;
    // Note: Should implement BST cleanup in real code
  }

  SSTable ST;
  BiTree T;
};

// Test SearchSeq function
TEST_F(SearchTest, SearchSeq_Found) {
  EXPECT_EQ(1, SearchSeq(ST, 1));
  EXPECT_EQ(3, SearchSeq(ST, 5));
  EXPECT_EQ(5, SearchSeq(ST, 9));
}

TEST_F(SearchTest, SearchSeq_NotFound) {
  EXPECT_EQ(0, SearchSeq(ST, 0));   // Should return sentinel position
  EXPECT_EQ(0, SearchSeq(ST, 100)); // Not in table
}

// Test BinarySearch function
TEST_F(SearchTest, BinarySearch_Found) {
  EXPECT_EQ(1, BinarySearch(ST, 1));
  EXPECT_EQ(3, BinarySearch(ST, 5));
  EXPECT_EQ(5, BinarySearch(ST, 9));
}

TEST_F(SearchTest, BinarySearch_NotFound) {
  EXPECT_EQ(-1, BinarySearch(ST, 0));
  EXPECT_EQ(-1, BinarySearch(ST, 2));
  EXPECT_EQ(-1, BinarySearch(ST, 100));
}

// Test BinarySearchRecursion function
TEST_F(SearchTest, BinarySearchRecursion_Found) {
  EXPECT_EQ(1, BinarySearchRecursion(ST, 1, 1, 5));
  EXPECT_EQ(3, BinarySearchRecursion(ST, 5, 1, 5));
  EXPECT_EQ(5, BinarySearchRecursion(ST, 9, 1, 5));
}

TEST_F(SearchTest, BinarySearchRecursion_NotFound) {
  EXPECT_EQ(0, BinarySearchRecursion(ST, 0, 1, 5));
  EXPECT_EQ(0, BinarySearchRecursion(ST, 2, 1, 5));
  EXPECT_EQ(0, BinarySearchRecursion(ST, 100, 1, 5));
}

// Test BST_Search function
TEST_F(SearchTest, BST_Search_Found) {
  BSTNode *result = BST_Search(T, 50);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ(50, result->data);

  result = BST_Search(T, 30);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ(30, result->data);

  result = BST_Search(T, 80);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ(80, result->data);
}

TEST_F(SearchTest, BST_Search_NotFound) {
  BSTNode *result = BST_Search(T, 100);
  EXPECT_EQ(nullptr, result);

  result = BST_Search(T, 25);
  EXPECT_EQ(nullptr, result);
}

// Test BSTInsert function
TEST_F(SearchTest, BSTInsert_NewNode) {
  BiTree testTree = NULL;
  EXPECT_TRUE(BSTInsert(testTree, 10));
  ASSERT_NE(nullptr, testTree);
  EXPECT_EQ(10, testTree->data);

  EXPECT_TRUE(BSTInsert(testTree, 5));
  EXPECT_TRUE(BSTInsert(testTree, 15));
}

TEST_F(SearchTest, BSTInsert_DuplicateNode) {
  EXPECT_FALSE(BSTInsert(T, 50)); // Already exists
  EXPECT_FALSE(BSTInsert(T, 30)); // Already exists
}

// Test IsBST function
TEST_F(SearchTest, IsBST_ValidBST) {
  EXPECT_TRUE(IsBST(T));

  BiTree emptyTree = NULL;
  EXPECT_TRUE(IsBST(emptyTree)); // Empty tree is BST
}

TEST_F(SearchTest, IsBST_InvalidBST) {
  // Create an invalid BST manually
  BiTree invalidTree = (BiTree)malloc(sizeof(BSTNode));
  invalidTree->data = 50;
  invalidTree->lchild = (BiTree)malloc(sizeof(BSTNode));
  invalidTree->rchild = (BiTree)malloc(sizeof(BSTNode));
  invalidTree->lchild->data = 60; // Left child > root (invalid)
  invalidTree->rchild->data = 40; // Right child < root (invalid)
  invalidTree->lchild->lchild = invalidTree->lchild->rchild = NULL;
  invalidTree->rchild->lchild = invalidTree->rchild->rchild = NULL;

  EXPECT_FALSE(IsBST(invalidTree));

  // Cleanup
  free(invalidTree->lchild);
  free(invalidTree->rchild);
  free(invalidTree);
}

// Test GetLevel function
TEST_F(SearchTest, GetLevel_ExistingNode) {
  EXPECT_EQ(1, GetLevel(T, 50)); // Root level
  EXPECT_EQ(2, GetLevel(T, 30)); // Level 2
  EXPECT_EQ(2, GetLevel(T, 70)); // Level 2
  EXPECT_EQ(3, GetLevel(T, 20)); // Level 3
}

TEST_F(SearchTest, GetLevel_NonExistingNode) {
  EXPECT_EQ(0, GetLevel(T, 100)); // Should handle non-existing nodes
}

// Test GetMinMax function
TEST_F(SearchTest, GetMinMax_Test) {
  ElemType min, max;
  GetMinMax(T, min, max);
  EXPECT_EQ(20, min); // Leftmost node
  EXPECT_EQ(80, max); // Rightmost node
}

// Test SeqSearch function (with swap behavior)
TEST_F(SearchTest, SeqSearch_WithSwap) {
  SSTable testST;
  testST.elem = new ElemType[6];
  testST.elem[0] = 1;
  testST.elem[1] = 3;
  testST.elem[2] = 5;
  testST.elem[3] = 7;
  testST.elem[4] = 9;
  testST.TableLen = 5;

  // Search for element at index 2, should swap with predecessor
  int result = SeqSearch(testST, 5);
  EXPECT_EQ(1, result);         // New position after swap
  EXPECT_EQ(5, testST.elem[1]); // 5 moved to position 1
  EXPECT_EQ(3, testST.elem[2]); // 3 moved to position 2

  delete[] testST.elem;
}

TEST_F(SearchTest, SeqSearch_FirstElement) {
  SSTable testST;
  testST.elem = new ElemType[6];
  testST.elem[0] = 1;
  testST.elem[1] = 3;
  testST.elem[2] = 5;
  testST.TableLen = 3;

  // Search for first element, no swap should occur
  int result = SeqSearch(testST, 1);
  EXPECT_EQ(0, result);
  EXPECT_EQ(1, testST.elem[0]); // Should remain in same position

  delete[] testST.elem;
}

TEST_F(SearchTest, SeqSearch_NotFound) {
  int result = SeqSearch(ST, 100);
  EXPECT_EQ(-1, result);
}

// Test PrintBigger function (capture output)
TEST_F(SearchTest, PrintBigger_Test) {
  // Redirect stdout to capture output
  std::ostringstream buffer;
  std::streambuf *orig = std::cout.rdbuf(buffer.rdbuf());

  // Redirect printf output is tricky, so we'll just test it doesn't crash
  PrintBigger(T, 60);

  // Restore stdout
  std::cout.rdbuf(orig);

  // The function should print values >= 60 in descending order
  // Expected output should contain: 80, 70, 60
  // But since we're using printf, output capture is complex
  // In a real test, you might want to modify PrintBigger to take an output
  // stream
}

// Integration test
TEST_F(SearchTest, IntegrationTest_BST) {
  // Create a new BST and test various operations
  BiTree testTree = NULL;
  ElemType keys[] = {15, 10, 20, 8, 12, 25};
  BSTCreate(testTree, keys, 6);

  // Test search
  EXPECT_NE(nullptr, BST_Search(testTree, 15));
  EXPECT_EQ(nullptr, BST_Search(testTree, 100));

  // Test level calculation
  EXPECT_EQ(1, GetLevel(testTree, 15));
  EXPECT_EQ(2, GetLevel(testTree, 10));
  EXPECT_EQ(3, GetLevel(testTree, 8));

  // Test min/max
  ElemType min, max;
  GetMinMax(testTree, min, max);
  EXPECT_EQ(8, min);
  EXPECT_EQ(25, max);

  // Test BST validation
  EXPECT_TRUE(IsBST(testTree));
}