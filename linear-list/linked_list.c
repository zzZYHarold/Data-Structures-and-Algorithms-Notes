//
// Created by zyh on 2026/7/14.
//

#include <stdio.h>
#include <stdlib.h>
// 链表
typedef int T;
typedef struct ListNode* Node;   //这里我们直接为结点指针起别名，可以直接作为表实现

struct ListNode {
    T element;   //保存当前元素
    struct ListNode * next;   //指向下一个结点的指针
};

void initList(Node head) {
    head->next = NULL;
}

_Bool insertElement(Node head, T element, int index) {  // index 依然是位序s, 头节点记为0
    // 合法检查
    if (index < 1)
        return 0;

    while (--index) {
        head = head->next;
        if (head == NULL)  // 越界
            return 0;
    }

    Node new_node = malloc(sizeof(struct ListNode));
    if (!new_node)
        return 0;
    new_node->element = element;
    new_node->next = head->next;
    head->next = new_node;

    return 1;
}

_Bool deleteElement(Node head, int index) {
    // 合法检查
    if (index < 1)
        return 0;

    while (--index) {
        head = head->next;
        if (head == NULL)  // 越界
            return 0;
    }
    if (!head->next)
        return 0;

    Node tmp = head->next;
    head->next = tmp->next;

    free(tmp);
    return 1;
}

T* getElement(Node head, int index) {
    // 合法检查
    if (index < 1)
        return 0;

    while (--index) {
        head = head->next;
        if (head == NULL)  // 越界
            return 0;
    }
    return &head->next->element;
}

int findElementIndex(Node head, T element) {
    int i = 1;
    head = head->next;

    while (head) {
        if (head->element == element)
            return i;
        i++;
        head = head->next;
    }

    return -1;
}

int sizeList(Node head) {
    int size = -1;
    while (head) {
        size++;
        head = head->next;
    }

    return size;
}

void printList(Node head){
    while (head->next) {
        head = head->next;
        printf("%d ", head->element);   //因为头结点不存放数据，所以从第二个开始打印
    }
}

int main() {
    struct ListNode head;
    initList(&head);
    for (int i = 1; i <= 3; ++i) {  // 按位序，1base
        insertElement(&head, i * 100, i);   //依次插入3个元素
    }
    printList(&head);   //打印一下看看
}
