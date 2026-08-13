//
// Created by zyh on 2026/7/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 线索化二叉树

/*
        A
       / \
      B   C
     / \
    D   E
*/

typedef char T;

typedef struct TreeNode {
    T element;
    struct TreeNode * left;
    struct TreeNode * right;
    bool leftTag, rightTag;   //标志位，如果为true表示这一边指针指向的是线索，false就是正常的孩子结点
} *Node;

Node createNode(T element){   //单独写了个函数来创建结点
    Node node = malloc(sizeof(struct TreeNode));
    node->element = element;
    node->left = node->right = NULL;
    node->rightTag = node->leftTag = false;

    return node;
}

Node pre = NULL;  //这里我们需要一个pre来保存后续结点的指向
void preOrderThreaded(Node target) {   //前序遍历线索化函数
    if(target == NULL)
        return;

    if(target->left == NULL) {   //首先判断当前结点左边是否为NULL，如果是，那么指向上一个结点
        target->left = pre;
        target->leftTag = true;  //记得修改标记
    }
    if(pre && pre->right == NULL) {  //然后是判断上一个结点的右边是否为NULL，如果是那么进行线索化，指向当前结点
        pre->right = target;
        pre->rightTag = true;  //记得修改标记
    }

    pre = target;   //每遍历完一个，需要更新一下pre，表示上一个遍历的结点

    if(!target->leftTag)   //注意只有标志位是0才可以继续向下，否则就是线索了
        preOrderThreaded(target->left);
    if(!target->rightTag)
        preOrderThreaded(target->right);
}

void preOrder(Node node) {
    while (node) {
        printf("%c", node->element);

        if (!node->leftTag)
            node = node->left;
        else
            node = node->right;
    }
}

int main() {
    Node a = createNode('A');
    Node b = createNode('B');
    Node c = createNode('C');
    Node d = createNode('D');
    Node e = createNode('E');

    a->left = b;
    b->left = d;
    a->right = c;
    b->right = e;

    preOrderThreaded(a);
    preOrder(a);    // ABDEC

    free(a), free(b), free(c),
    free(d), free(e);
}