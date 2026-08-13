//
// Created by zyh on 2026/8/7.
//

#include <stdio.h>
#include <stdlib.h>

// 邻接表--无权有向图

#define MaxVertex 5

typedef char E;

/* ---------- 邻接表中的普通结点 ---------- */
/*
 * 普通结点不需要保存顶点的数据，
 * 只需要保存“连接到了哪个顶点”。
 */
typedef struct Node {
    int nextVertex;          // 邻接顶点的编号
    struct Node* next;
} *Node;

/* ---------- 每个顶点对应的头结点 ---------- */
/*
 * 头结点保存：
 *
 * 1. 顶点本身的数据
 * 2. 该顶点的邻接链表
 */
typedef struct {
    E element;
    Node next;
} HeadNode;

/* ---------- 图 ---------- */
typedef struct ListGraph {
    int vertexCount;             // 当前顶点数
    int edgeCount;               // 当前边数

    HeadNode vertex[MaxVertex];  // 所有顶点
} *Graph;

/**
 * 创建一个空图
 */
Graph create() {
    Graph graph = malloc(sizeof(struct ListGraph));
    if (!graph)
        return NULL;

    graph->vertexCount = graph->edgeCount = 0;
    return graph;
}

/**
 * 添加顶点
 */
void addVertex(Graph graph, E element) {
    if (!graph || graph->vertexCount >= MaxVertex)
        return;

    int index = graph->vertexCount;
    graph->vertex[index].element = element;
    graph->vertex[index].next = NULL;
    graph->vertexCount++;
}

/**
 * 添加有向边
 *
 * a -> b
 */
void addEdge(Graph graph, int a, int b) {
    if (!graph)
        return;
    if (a < 0 || a >= graph->vertexCount ||
        b < 0 || b >= graph->vertexCount)
        return;

    /*
     * 先遍历 a 的邻接链表：
     *
     * 1. 检查 a -> b 是否已经存在
     * 2. 顺便找到链表最后一个结点
     */
    Node curr = graph->vertex[a].next;
    Node tail = NULL;

    while (curr) {
        // 已经存在 a -> b
        if (curr->nextVertex == b)
            return;

        tail = curr;
        curr = curr->next;
    }

    /*
     * 确认不存在重复边以后，
     * 再创建新的边结点。
     */
    Node newNode = malloc(sizeof(struct Node));
    if (!newNode)
        return;

    newNode->nextVertex = b;
    newNode->next = NULL;

    /*
     * tail == NULL：
     * a 当前还没有任何邻接顶点
     *
     * 否则：
     * 挂到链表末尾
     */
    if (tail == NULL)
        graph->vertex[a].next = newNode;
    else
        tail->next = newNode;

    graph->edgeCount++;
}

/**
 * 打印邻接表
 */
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

/**
 * 释放图
 */
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

int main() {
    Graph graph = create();

    for (char c = 'A'; c <= 'D'; ++c)
        addVertex(graph, c);

    addEdge(graph, 0, 1);   // A -> B
    addEdge(graph, 1, 2);   // B -> C
    addEdge(graph, 2, 3);   // C -> D
    addEdge(graph, 3, 0);   // D -> A
    addEdge(graph, 2, 0);   // C -> A

    // printf("vertexCount = %d\n", graph->vertexCount);
    printGraph(graph);

    destroyGraph(graph);
    return 0;
}
