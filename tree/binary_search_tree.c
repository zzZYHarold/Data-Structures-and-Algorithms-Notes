//
// Created by zyh on 2026/7/25.
//

#include <stdio.h>
#include <stdlib.h>

// 二叉搜索树

/*
        18
       /  \
     10    22
    /  \
   7   15
    \
     9
    /
   8
*/

typedef int T;

typedef struct TreeNode {
    T element;
    struct TreeNode * left;
    struct TreeNode * right;
} * Node;

Node createNode(T element){
    Node node = malloc(sizeof(struct TreeNode));
    node->element = element;
    node->left = node->right = NULL;

    return node;
}

Node insert(Node root, T element) {
    if (root) {
        if (root->element > element)
            root->left = insert(root->left, element);
        else if (root->element < element)
            root->right = insert(root->right, element);
    }
    else {
        root = createNode(element);
    }

    return root;
}

Node find(Node root, T target) {
    while (root) {
        if (root->element > target)
            root = root->left;
        else if (root->element < target)
            root = root->right;
        else
            return root;
    }

    return NULL;
}

Node findMax(Node root) {   //查找最大值就更简单了，最右边的一定是最大的
    while (root && root->right)
        root = root->right;
    return root;
}

Node removeNode(Node root, T target) {
    if (!root)
        return NULL;

    if (root->element > target)
        root->left = removeNode(root->left, target);
    else if (root->element < target)
        root->right = removeNode(root->right, target);
    else {  // 找到了，递归下来的 "root" 即为要删掉的节点。
        if (root->left && root->right) {  // “要删除的节点有左右孩子”
            Node max = findMax(root->left);  // 这里采用“选取其左子树中最大结点上位”
            root->element = max->element;  // 替换element
            root->left = removeNode(root->left, max->element);  // 删除max节点对应的节点
        }
        else {  // “要删除的结点是叶子结点”、“要删除的结点是只有一个孩子结点”两种情况一起处理
            Node temp = root;
            if (root->right)
                root = root->right;
            else
                root = root->left;
            free(temp);
        }
    }

    return root;
}

void preOrder(Node target) {  // 前序遍历-递归
    if (target == NULL)
        return;

    printf("%d ", target->element);
    preOrder(target->left);
    preOrder(target->right);
}

int main() {
    Node root = insert(NULL, 18);
    insert(root, 10);
    insert(root, 7);
    insert(root, 15);
    insert(root, 22);
    insert(root, 9);
    insert(root, 8);

    preOrder(root);

    removeNode(root, 9);

    printf("\n");
    preOrder(root);
}