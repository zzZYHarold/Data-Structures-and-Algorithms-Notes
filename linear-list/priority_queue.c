//
// Created by zyh on 2026/7/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 优先队列

typedef int T;

typedef struct LNode {
    T element;
    struct LNode* next;
} * Node;

typedef struct Queue {
    Node head, tail;
} * LLQueue;

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

_Bool enqueue(LLQueue queue, T element) {  // 优先队列入队
    Node node = malloc(sizeof(struct LNode));
    if (!node)
        return 0;

    node->element = element;
    node->next = NULL;

    Node pre = queue->head;
    while (pre->next && pre->next->element >= element)  // 我们从头结点开始往后挨个看，直到找到第一个小于当前值的结点，或者到头为止
        pre = pre->next;

    if (pre == queue->tail) {  // 如果说找到的位置已经是最后了，那么直接插入就行
        queue->tail->next = node;
        queue->tail = node;
    }
    else {
        node->next = pre->next;
        pre->next = node;
    }

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

    enqueue(&queue, 9);
    enqueue(&queue, 4);
    enqueue(&queue, 7);
    enqueue(&queue, 3);
    enqueue(&queue, 13);

    printQueue(&queue);
}