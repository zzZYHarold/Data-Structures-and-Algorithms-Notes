//
// Created by zyh on 2026/7/16.
//

#include <stdio.h>
#include <stdlib.h>
// 栈FILO by 链表

typedef int T;

struct ListNode {
    T element;   //保存当前元素
    struct ListNode * next;   //指向下一个结点的指针
};

typedef struct ListNode* Node;   //这里我们直接为结点指针起别名，可以直接作为表实现

void initStack(Node head) {
    head->next = NULL;
}

_Bool push(Node head, T element) {
    Node new_node = malloc(sizeof(struct ListNode));
    if (!new_node)
        return 0;

    new_node->element = element;
    new_node->next = head->next;
    head->next = new_node;

    return 1;
}

T pop(Node head) {
    Node temp = head->next;
    T ele = temp->element;

    head->next = temp->next;
    free(temp);
    return ele;
}

_Bool isEmpty(Node head) {
    return head->next == NULL;
}

void printStack(Node head){
    printf("| ");
    head = head->next;
    while(head) {
        printf("%d ", head->element);
        head = head->next;
    }
    printf("\n");
}

int main(){
    struct ListNode head;
    initStack(&head);
    for (int i = 0; i < 3; ++i) {
        push(&head, i*100);
    }
    printStack(&head);
    while (!isEmpty(&head)) {
        printf("%d ", pop(&head));   //将栈中所有元素依次出栈
    }
}