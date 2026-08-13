//
// Created by zyh on 2026/7/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// 队列FIFO

typedef int T;

struct Queue {
    T* array;
    int capacity;
    int front;
    int rear;
};

typedef struct Queue* ArrayQueue;

_Bool initQueue(ArrayQueue queue) {
    queue->array = malloc(sizeof(T) * 10);
    if(queue->array == NULL)
        return 0;
    queue->capacity = 10;
    queue->front = queue->rear = 0;   //默认情况下队首和队尾都指向0的位置

    return 1;
}

_Bool enqueue(ArrayQueue queue, T element) {  // 入队
    int pos = (queue->rear + 1) % queue->capacity;
    if (pos == queue->front)  // 满了
        return 0;
    queue->rear = pos;
    queue->array[queue->rear] = element;

    return 1;
}

T dequeue(ArrayQueue queue) {
    assert(queue->rear != queue->front);
    queue->front = (queue->front + 1) % queue->capacity;
    return queue->array[queue->front];
}

_Bool isEmpty(ArrayQueue queue) {
    return queue->rear == queue->front;
}

void printQueue(ArrayQueue queue) {
    if (isEmpty(queue)) {
        printf("队列为空\n");
        return;
    }
    printf("<<< ");
    int i = queue->front;
    while (i != queue->rear) {
        i = (i + 1) % queue->capacity;
        printf("%d ", queue->array[i]);
    }
    printf("<<<\n");
}

int main(){
    struct Queue queue;
    initQueue(&queue);
    for (int i = 0; i < 5; ++i) {
        enqueue(&queue, i * 100);
    }
    printQueue(&queue);
    while (!isEmpty(&queue)) {
        printf("%d ", dequeue(&queue));
    }
}