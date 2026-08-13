//
// Created by zyh on 2026/7/16.
//

#include <stdio.h>
#include <stdlib.h>
// 双向链表

typedef int T;
typedef struct ListNode * Node;

struct ListNode {
    T element;   //保存当前元素
    struct ListNode * next;   //指向下一个结点的指针
    struct ListNode * prev;   //指向上一个结点的指针
};

void initList(Node head) {
    head->next = head->prev = NULL;
}

_Bool insertElement(Node head, T element, int index) {
    if (index < 1)
        return 0;
    while (--index) {
        head = head->next;
        if (!head)
            return 0;
    }

    Node new_node = malloc(sizeof(struct ListNode));
    if (!new_node)
        return 0;

    new_node->element = element;
    if (head->next) {
        new_node->next = head->next;
        head->next->prev = new_node;
    }
    else {
        new_node->next = NULL;
    }
    head->next = new_node;
    new_node->prev = head;

    return 1;
}

_Bool deleteElement(Node head, int index) {
    if (index < 1)
        return 0;
    while (--index) {
        head = head->next;
        if (!head)
            return 0;
    }
    if (!head->next)
        return 0;

    Node temp = head->next;
    if (temp->next) {
        temp->next->prev = head;
        head->next = temp->next;
    }
    else {
        head->next = NULL;
    }

    free(temp);
    return 1;
}

int main() {
    struct ListNode head;
    initList(&head);
    for (int i = 1; i <= 5; ++i)  //插5个元素吧
        insertElement(&head, i * 100, i);

    Node node = &head;   //先来正向遍历一次
    do {
        node = node->next;
        printf("%d -> ", node->element);
    } while (node->next != NULL);

    printf("\n");   //再来反向遍历一次
    do {
        printf("%d -> ", node->element);
        node = node->prev;
    } while (node->prev != NULL);
}
