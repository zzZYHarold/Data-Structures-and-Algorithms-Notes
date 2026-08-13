//
// Created by zyh on 2026/7/28.
//

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 哈夫曼树：通过优先队列构建

typedef char E;

// ==================== 哈夫曼树部分 ====================

typedef struct TreeNode {
    E element;                  // 叶子结点保存字符，内部结点可设为 '\0'
    int value;                  // 权值

    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode, * TNode;

TNode createTreeNode(E element, int value) {
    TNode node = malloc(sizeof(TreeNode));

    if (node == NULL)
        return NULL;

    node->element = element;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// ==================== 优先队列部分 ====================

// 队列中的每个元素是一棵哈夫曼树的根结点指针
typedef struct QueueNode {
    TNode root;
    struct QueueNode* next;
} QueueNode;

typedef struct PriorityQueue {
    QueueNode* head;    // 虚拟头结点
    QueueNode* tail;    // 尾结点
    size_t size;
} PriorityQueue;

bool initQueue(PriorityQueue* queue) {
    if (queue == NULL)
        return false;

    QueueNode* node = malloc(sizeof(QueueNode));

    if (node == NULL)
        return false;
    
    node->root = NULL;
    node->next = NULL;

    queue->head = node;
    queue->tail = node;
    queue->size = 0;

    return true;
}

bool isEmpty(const PriorityQueue* queue) {
    return queue == NULL || queue->size == 0;
}

/*
 * 按树根结点的权值从小到大插入。
 *
 * 例如依次插入权值：
 * 8、3、5
 *
 * 队列最终为：
 * 3 -> 5 -> 8
 */
bool enqueue(PriorityQueue* queue, TNode tree) {
    if (queue == NULL || tree == NULL)
        return false;

    QueueNode* node = malloc(sizeof(QueueNode));

    if (node == NULL)
        return false;

    node->root = tree;
    node->next = NULL;

    QueueNode* previous = queue->head;

    /*
     * previous->next->root 是队列中原有的树(的根)结点。
     * tree 是当前准备插入的树(的根)结点。
     *
     * <= 表示遇到相同权值时，插在已有相同权值结点的后面。
     */
    while (previous->next != NULL && previous->next->root->value <= tree->value)
        previous = previous->next;

    node->next = previous->next;
    previous->next = node;

    // 如果插入到了链表末尾，需要更新 tail
    if (node->next == NULL)
        queue->tail = node;

    queue->size++;
    return true;
}

// 取出并删除权值最小的树
TNode dequeue(PriorityQueue *queue) {
    assert(queue != NULL);
    assert(!isEmpty(queue));

    QueueNode* first = queue->head->next;
    TNode toDelete = first->root;

    queue->head->next = first->next;

    // 原来只有一个有效结点
    if (queue->tail == first)
        queue->tail = queue->head;

    free(first);
    queue->size--;

    return toDelete;
}

void printQueue(const PriorityQueue *queue) {
    if (queue == NULL)
        return;

    printf("<<< ");

    QueueNode* curr = queue->head->next;

    while (curr != NULL) {
        TNode node = curr->root;

        if (node->element == '\0')  // 内部结点
            printf("[internal:%d] ", node->value);
        else  // 叶子结点
            printf("[%c:%d] ", node->element, node->value);

        curr = curr->next;
    }

    printf("<<<\n");
}

// 只释放队列链表结点，不释放其中指向的哈夫曼树
void destroyQueue(PriorityQueue* queue) {
    if (queue == NULL)
        return;

    QueueNode* curr = queue->head;

    while (curr != NULL) {
        QueueNode* next = curr->next;
        free(curr);
        curr = next;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

// ==================== 构建哈夫曼树 ====================

TNode buildHuffmanTree(const E elements[], const int values[], size_t count) {
    if (elements == NULL || values == NULL || count == 0)
        return NULL;

    PriorityQueue queue;

    if (!initQueue(&queue))
        return NULL;

    // 每个字符先单独作为一棵只有一个结点的树
    for (size_t i = 0; i < count; i++) {
        TNode leaf = createTreeNode(elements[i], values[i]);

        if (leaf == NULL || !enqueue(&queue, leaf)) {
            destroyQueue(&queue);
            return NULL;
        }
    }

    /*
     * 每次取出权值最小的两棵树：
     *
     *      parent
     *      /    \
     *   first  second
     *
     * parent 的权值等于二者权值之和，
     * 然后把 parent 重新放回优先队列。
     */
    while (queue.size > 1) {
        TNode first = dequeue(&queue);
        TNode second = dequeue(&queue);

        TNode parent = createTreeNode('\0', first->value + second->value);

        if (parent == NULL) {
            destroyQueue(&queue);
            return NULL;
        }

        parent->left = first;
        parent->right = second;

        enqueue(&queue, parent);
    }

    // 队列中最后剩下的树就是完整哈夫曼树
    TNode root = dequeue(&queue);

    destroyQueue(&queue);

    return root;
}

// 前序打印，仅用于观察结构
void preorder(TNode root) {
    if (root == NULL)
        return;

    if (root->element == '\0')
        printf("internal(%d) ", root->value);
    else
        printf("%c(%d) ", root->element, root->value);

    preorder(root->left);
    preorder(root->right);
}

void destroyTree(TNode root) {
    if (root == NULL)
        return;

    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

// ==================== 测试 ====================

int main(void) {
    // 设置控制台输出编码为 UTF-8
    SetConsoleOutputCP(65001);

    E elements[] = {'A', 'B', 'C', 'D'};
    int values[] = {5, 7, 2, 13};

    size_t count = sizeof(elements) / sizeof(elements[0]);

    TNode root = buildHuffmanTree(elements, values, count);

    if (root == NULL) {
        fprintf(stderr, "哈夫曼树构建失败\n");
        return EXIT_FAILURE;
    }

    printf("根结点总权值：%d\n", root->value);

    printf("前序遍历：");
    preorder(root);
    printf("\n");

    destroyTree(root);

    return EXIT_SUCCESS;
}