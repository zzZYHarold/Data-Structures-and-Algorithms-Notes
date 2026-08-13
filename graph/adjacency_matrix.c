//
// Created by zyh on 2026/8/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 邻接矩阵--无权有向图

#define MaxVertex 5

typedef char E;

typedef struct MatrixGraph {
    int vertexCount;                  // 当前顶点数
    int edgeCount;                    // 当前边数

    int matrix[MaxVertex][MaxVertex]; // 邻接矩阵
    E data[MaxVertex];                // 每个顶点对应的数据
} *Graph;

/**
 * 创建一个空图
 */
Graph create() {
    Graph graph = malloc(sizeof(struct MatrixGraph));
    if (!graph)
        return NULL;

    graph->vertexCount = graph->edgeCount = 0;

    // 初始化邻接矩阵
    memset(graph->matrix, 0, sizeof(graph->matrix));

    return graph;
}

/**
 * 添加顶点
 */
void addVertex(Graph graph, E element) {
    if (!graph || graph->vertexCount >= MaxVertex)
        return;

    graph->data[graph->vertexCount++] = element;
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

    // 防止重复添加同一条边
    if (graph->matrix[a][b] == 0) {
        graph->matrix[a][b] = 1;
        graph->edgeCount++;
    }
}

/**
 * 打印邻接矩阵
 */
void printGraph(Graph graph) {
    if (graph == NULL)
        return;

    // 打印列顶点
    printf("    ");
    for (int i = 0; i < graph->vertexCount; ++i)
        printf("%3c", graph->data[i]);

    putchar('\n');

    // 打印邻接矩阵
    for (int i = 0; i < graph->vertexCount; ++i) {
        // 行顶点
        printf("%3c ", graph->data[i]);

        for (int j = 0; j < graph->vertexCount; ++j)
            printf("%3d", graph->matrix[i][j]);

        putchar('\n');
    }
}

int main() {
    Graph graph = create();

    // 添加顶点
    addVertex(graph, 'A');    // 0
    addVertex(graph, 'B');    // 1
    addVertex(graph, 'C');    // 2
    addVertex(graph, 'D');    // 3

    // 添加有向边
    addEdge(graph, 0, 1);     // A -> B
    addEdge(graph, 0, 2);     // A -> C
    addEdge(graph, 1, 2);     // B -> C
    addEdge(graph, 2, 3);     // C -> D
    addEdge(graph, 3, 1);     // D -> B

    printf("vertexCount = %d\n", graph->vertexCount);
    printf("edgeCount   = %d\n\n", graph->edgeCount);

    printGraph(graph);

    free(graph);
    return 0;
}
