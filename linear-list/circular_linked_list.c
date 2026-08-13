//
// Created by zyh on 2026/7/16.

//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>   // 使用 bool, true, false
// 双向循环链表（带哨兵头节点）

typedef int T;

struct ListNode {
    T element;
    struct ListNode *next;
    struct ListNode *prev;
};

typedef struct ListNode * Node;

// 初始化：空循环链表，头节点自环
void initList(Node head) {
    head->next = head;
    head->prev = head;
}

// 在指定位置（位序，从1开始）之后插入元素
// 插入后新节点位于第 index 个位置（1 <= index <= 当前长度+1）
bool insertElement(Node head, T element, int index) {
    if (head == NULL || index < 1)
        return false;

    // 找到第 index-1 个节点（即插入位置的前驱）
    Node cur = head;
    for (int i = 1; i < index; ++i) {
        cur = cur->next;
        if (cur == head)   // 说明 index 越界（超过了链表长度+1）
            return false;
    }

    Node new_node = (Node)malloc(sizeof(struct ListNode));
    if (!new_node)
        return false;

    new_node->element = element;

    // 双向循环插入（四步连接）
    new_node->next = cur->next;
    new_node->prev = cur;
    cur->next->prev = new_node;
    cur->next = new_node;

    return true;
}

// 删除第 index 个节点（1 <= index <= 当前长度）
bool deleteElement(Node head, int index) {
    if (head == NULL || index < 1)
        return false;

    Node cur = head;
    for (int i = 1; i <= index; ++i) {
        cur = cur->next;
        if (cur == head)   // 要删除的节点不存在（越界）
            return false;
    }
    // 此时 cur 指向待删除节点

    // 从循环链表中摘下 cur
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;

    free(cur);
    return true;
}

// 正向遍历（从头节点下一个开始，直到回到头节点）
void forwardTraverse(Node head) {
    if (head == NULL) return;
    Node cur = head->next;
    while (cur != head) {
        printf("%d -> ", cur->element);
        cur = cur->next;
    }
    printf("(head)\n");
}

// 反向遍历（从尾节点开始，直到回到头节点）
void backwardTraverse(Node head) {
    if (head == NULL) return;
    Node cur = head->prev;   // 尾节点
    while (cur != head) {
        printf("%d -> ", cur->element);
        cur = cur->prev;
    }
    printf("(head)\n");
}

int main() {
    struct ListNode head;
    initList(&head);

    // 插入5个元素：100, 200, 300, 400, 500（分别插到第1~5位）
    for (int i = 1; i <= 5; ++i) {
        insertElement(&head, i * 100, i);
    }

    printf("正向遍历：");
    forwardTraverse(&head);

    printf("反向遍历：");
    backwardTraverse(&head);

    // 删除第3个元素（300）
    deleteElement(&head, 3);
    printf("删除第3个元素后，正向遍历：");
    forwardTraverse(&head);

    // 在位置2插入 666（插入后顺序：100, 666, 200, 400, 500）
    insertElement(&head, 666, 2);
    printf("在位置2插入666后，正向遍历：");
    forwardTraverse(&head);

    return 0;
}