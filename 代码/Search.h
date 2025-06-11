#ifndef SEARCH_H
#define SEARCH_H

#include "stdafx.h"

typedef struct {  // 顺序查找表
  ElemType *elem; // 元素存储空间基地址
  int TableLen;   // 表长
} SSTable;

typedef struct BSTNode {           // 链式存储的BST
  ElemType data;                   // 数据域
  struct BSTNode *lchild, *rchild; // 左右孩子指针
  int count;                       // 记录子树结点数（7.3 11题用）
} BSTNode, *BiTree;

typedef int KeyType;

// Function declarations

// Sequential search functions
int SearchSeq(SSTable ST, ElemType key);
int SeqSearch(SSTable ST, ElemType key); // With swap behavior

// Binary search functions
int BinarySearch(SSTable ST, ElemType key);
int BinarySearchRecursion(SSTable ST, ElemType key, int low, int high);

// Binary Search Tree functions
BSTNode *BST_Search(BiTree T, ElemType key);
bool BSTInsert(BiTree &T, ElemType key);
void BSTCreate(BiTree &T, ElemType key[], int n);

// BST utility functions
bool IsBST(BiTree T);
int GetLevel(BiTree T, ElemType e);
void GetMinMax(BiTree T, ElemType &min, ElemType &max);
void PrintBigger(BiTree T, ElemType k);
BSTNode *KthSmall(BiTree T, int k);

#endif // SEARCH_H