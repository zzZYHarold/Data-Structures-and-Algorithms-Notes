//
// Created by zyh on 2026/7/22.
//

#include <stdio.h>
#include <stdlib.h>
// 二叉树-构建

typedef char T;

struct TreeNode {
    T element;    //存放元素
    struct TreeNode* left;   //指向左子树的指针
    struct TreeNode* right;   //指向右子树的指针
};

typedef struct TreeNode* Node;

int main(){
    Node a = malloc(sizeof(struct TreeNode));   //依次创建好这五个结点
    Node b = malloc(sizeof(struct TreeNode));
    Node c = malloc(sizeof(struct TreeNode));
    Node d = malloc(sizeof(struct TreeNode));
    Node e = malloc(sizeof(struct TreeNode));
    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->left = c->right = NULL;
    d->left = d->right = NULL;
    e->left = e->right = NULL;

    free(a), free(b), free(c),
    free(d), free(e);

    return 0;
}