//
// Created by zyh on 2026/8/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// dfs--邻接表
// frontier = 调用栈，无需显式维护

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

// -------- dfs ---------
/**
 * 深度优先搜索
 *
 * @param graph         图
 * @param startVertex   当前搜索顶点的下标
 * @param targetVertex  目标顶点的下标
 * @param visited       已访问顶点数组
 *
 * @return 找到目标返回 true，否则返回 false
 */
bool dfs(Graph graph, int startVertex, int targetVertex, bool* visited) {
    // 访问当前顶点
    visited[startVertex] = true;
    printf("%c -> ", graph->vertex[startVertex].element);

    // 当前顶点就是目标顶点
    if (startVertex == targetVertex)
        return true;

    // 获取当前顶点的第一个邻接顶点
    Node node = graph->vertex[startVertex].next;

    while (node) {
        // 只访问没有访问过的顶点
        if (!visited[node->nextVertex])
            // 从邻接顶点继续向深处搜索
            if (dfs(graph, node->nextVertex, targetVertex, visited))
                return true;

        node = node->next;
    }
    // 当前分支以及后续所有分支都没找到
    return false;
}

/* python风格
_Bool dfs(Graph graph, int startVertex, int targetVertex) {
    int visited[MaxVertex] = {0};

    int stack[MaxVertex];
    int top = -1;

    // frontier.add(start)
    stack[++top] = startVertex;

    while (top >= 0) {
        // node = frontier.remove()
        int vertex = stack[top--];

        if (visited[vertex])
            continue;

        visited[vertex] = 1;

        printf("%c -> ", graph->vertex[vertex].element);

        if (vertex == targetVertex)
            return 1;

        Node node = graph->vertex[vertex].next;

        while (node) {
            if (!visited[node->nextVertex]) {
                // frontier.add(next)
                stack[++top] = node->nextVertex;
            }

            node = node->next;
        }
    }
    return 0;
}
 */