//
// Created by zyh on 2026/7/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// 队列FIFO

typedef int T;

struct LNode {
    T element;
    struct LNode* next;
};

typedef struct LNode* Node;

struct Queue {
    Node head, tail;
};

typedef struct Queue* LLQueue;

_Bool initQueue(LLQueue queue) {
    Node node = malloc(sizeof(struct LNode));
    if (!node)
        return 0;

    node->next = NULL;
    queue->head = queue->tail = node;
    return 1;
}

_Bool isEmpty(LLQueue queue) {
    return queue->head == queue->tail;
}

_Bool enqueue(LLQueue queue, T element) {
    Node node = malloc(sizeof(struct LNode));
    if (!node)
        return 0;

    node->element = element;
    node->next = NULL;
    queue->tail->next = node;
    queue->tail = node;

    return 1;
}

T dequeue(LLQueue queue) {
    assert(!isEmpty(queue));
    Node temp = queue->head->next;
    T ele = temp->element;
    queue->head->next = temp->next;

    if (queue->tail == temp) // temp->next == NULL
        queue->tail = queue->head;

    free(temp);
    return ele;
}

void printQueue(LLQueue queue){
    printf("<<< ");
    Node node = queue->head->next;
    while (1) {    //注意不能直接判空，因为前面我们没考虑，也就没将新结点next设定为NULL
        printf("%d ", node->element);
        if(node == queue->tail) break;    //当已经打印最后一个元素后，再结束
        else node = node->next;
    }
    printf("<<<\n");
}

int main(){
    struct Queue queue;
    initQueue(&queue);
    for (int i = 0; i < 5; ++i) {
        enqueue(&queue, i*100);
    }
    printQueue(&queue);
    while (!isEmpty(&queue)){
        printf("%d ", dequeue(&queue));
    }
}