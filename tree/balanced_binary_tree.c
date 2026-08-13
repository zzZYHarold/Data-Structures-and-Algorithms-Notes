//
// Created by zyh on 2026/7/26.
//

#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

typedef int T;

typedef struct TreeNode {
    T element;
    struct TreeNode * left;
    struct TreeNode * right;
    int height;   //每个结点需要记录当前子树的高度，便于计算平衡因子
} * Node;

Node createNode(T element){
    Node node = malloc(sizeof(struct TreeNode));
    node->element = element;
    node->height = 1;   //初始化时，高度写为1就可以了
    node->left = node->right = NULL;

    return node;
}

int getHeight(Node root) {
    if (!root)
        return 0;
    return root->height;
}

Node leftRotation(Node root) {  // 左旋操作
    Node new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    new_root->height = max(getHeight(new_root->left), getHeight(new_root->right)) + 1;
    return new_root;
}

Node rightRotation(Node root) {  // 右旋操作
    Node new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    new_root->height = max(getHeight(new_root->left), getHeight(new_root->right)) + 1;
    return new_root;
}

Node lrRotation(Node root) {  // LR型旋转调整
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

Node rlRotation(Node root) {  // LR型旋转调整
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

Node insert(Node root, T element) {
    if (!root) {  // 如果结点为NULL，说明找到了插入位置，直接创建新的就完事
        root = createNode(element);
    }
    else if (element < root->element) {  // 和二叉搜索树一样，判断大小，该走哪边走哪边，直到找到对应插入位置
        root->left = insert(root->left, element);  // 走左边

        if (getHeight(root->left) - getHeight(root->right) > 1) {  // 插入完成之后，需要计算平衡因子，看看是否失衡
            if (element < root->left->element )  // 接着需要判断一下是插入了左子树的左边还是右边
                root = rightRotation(root);  // 左边。LL型通过右旋得到新的根结点
            else
                root = lrRotation(root);  // 右边。LR型通过先左旋再右旋得到新的根结点
        }
    }
    else if (element > root->element) {
        root->right = insert(root->right, element);

        if (getHeight(root->left) - getHeight(root->right) < -1) {
            if (element > root->right->element )
                root = leftRotation(root);
            else
                root = rlRotation(root);
        }
    }

    // 前面的操作完成之后记得更新一下树高度
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    return root;
}
