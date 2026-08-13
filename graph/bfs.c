//
// Created by zyh on 2026/8/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// bfs--邻接表
// frontier = LLQueue，需要显式维护

#define MaxVertex 5

typedef char E;

typedef struct Node {
    int nextVertex;          // 邻接顶点的编号
    struct Node* next;
} *Node;

typedef struct {
    E element;
    Node next;
} HeadNode;

typedef struct ListGraph {
    int vertexCount;             // 当前顶点数
    int edgeCount;               // 当前边数

    HeadNode vertex[MaxVertex];  // 所有顶点
} *Graph;

Graph create() {
    Graph graph = malloc(sizeof(struct ListGraph));
    if (!graph)
        return NULL;

    graph->vertexCount = graph->edgeCount = 0;
    return graph;
}

void addVertex(Graph graph, E element) {
    if (!graph || graph->vertexCount >= MaxVertex)
        return;

    int index = graph->vertexCount;
    graph->vertex[index].element = element;
    graph->vertex[index].next = NULL;
    graph->vertexCount++;
}

void addEdge(Graph graph, int a, int b) {
    if (!graph)
        return;
    if (a < 0 || a >= graph->vertexCount ||
        b < 0 || b >= graph->vertexCount)
        return;

    Node curr = graph->vertex[a].next;
    Node tail = NULL;

    while (curr) {
        if (curr->nextVertex == b)
            return;

        tail = curr;
        curr = curr->next;
    }

    Node newNode = malloc(sizeof(struct Node));
    if (!newNode)
        return;

    newNode->nextVertex = b;
    newNode->next = NULL;

    if (tail == NULL)
        graph->vertex[a].next = newNode;
    else
        tail->next = newNode;

    graph->edgeCount++;
}

void printGraph(Graph graph) {
    if (graph == NULL)
        return;

    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%d | %c", i, graph->vertex[i].element);

        Node node = graph->vertex[i].next;

        while (node != NULL) {
            printf(" -> %d", node->nextVertex);
            node = node->next;
        }

        putchar('\n');
    }
}

void destroyGraph(Graph graph) {
    if (graph == NULL)
        return;

    for (int i = 0; i < graph->vertexCount; ++i) {
        Node node = graph->vertex[i].next;

        while (node != NULL) {
            Node next = node->next;
            free(node);
            node = next;
        }
    }
    free(graph);
}

//-------- 队列 --------

typedef int T;   // BFS 队列中存顶点下标

typedef struct LNode {
    T element;
    struct LNode *next;
} *QNode;

typedef struct Queue {
    QNode head, tail;
} *LLQueue;

bool initQueue(LLQueue queue) {
    QNode node = malloc(sizeof(struct LNode));
    if (!node)
        return false;

    node->next = NULL;

    // 使用哨兵头结点
    queue->head = queue->tail = node;

    return true;
}

bool isEmpty(LLQueue queue) {
    return queue->head == queue->tail;
}

bool enqueue(LLQueue queue, T element) {
    QNode node = malloc(sizeof(struct LNode));
    if (!node)
        return false;

    node->element = element;
    node->next = NULL;

    queue->tail->next = node;
    queue->tail = node;

    return true;
}

T dequeue(LLQueue queue) {
    assert(!isEmpty(queue));

    QNode temp = queue->head->next;
    T element = temp->element;
    queue->head->next = temp->next;

    // 如果删除的是队列中最后一个元素
    if (queue->tail == temp)
        queue->tail = queue->head;

    free(temp);
    return element;
}

void printQueue(LLQueue queue) {
    printf("<<< ");

    QNode node = queue->head->next;
    while (node != NULL) {
        printf("%d ", node->element);
        node = node->next;
    }

    printf("<<<\n");
}

void destroyQueue(LLQueue queue) {
    while (!isEmpty(queue))
        dequeue(queue);

    free(queue->head);
    queue->head = queue->tail = NULL;
}

//-------- bfs --------

/**
 * 广度优先搜索
 *
 * @param graph 图
 * @param startVertex 起点顶点下标
 * @param targetVertex 目标顶点下标
 * @param visited 已访问数组
 * @param queue 辅助队列
 *
 * @return 找到返回 true，否则返回 false
 */
bool bfs(Graph graph, int startVertex, int targetVertex, bool* visited, LLQueue queue) {
    enqueue(queue, startVertex);
    visited[startVertex] = true;

    while (!isEmpty(queue)) {
        int vertex = dequeue(queue);
        printf("%c -> ", graph->vertex[startVertex].element);

        // 当前顶点就是目标
        if (vertex == targetVertex)
            return true;

        Node node = graph->vertex[vertex].next;
        while (node) {
            if (!visited[node->nextVertex]) {
                enqueue(queue, node->nextVertex);

                // 入队时就标记为已访问
                visited[node->nextVertex] = true;
            }
            node = node->next;
        }
    }

    return false;
}