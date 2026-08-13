//
// Created by zyh on 2026/8/12.
//

#include <stdio.h>
#include <limits.h>

// 多源最短路径 / 任意两点之间最短路径--Floyd算法

#define MAX_VERTEX 100
#define INF (INT_MAX / 2)

typedef struct Graph {
    int vertexCount;
    int matrix[MAX_VERTEX][MAX_VERTEX];
} * Graph;


/*
 * 初始化图
 */
void initGraph(Graph graph, int vertexCount) {
    graph->vertexCount = vertexCount;

    for (int i = 0; i < vertexCount; ++i)
        for (int j = 0; j < vertexCount; ++j)
            if (i == j)
                graph->matrix[i][j] = 0;
            else
                graph->matrix[i][j] = INF;
}


/*
 * 添加有向边
 */
void addEdge(Graph graph, int from, int to, int weight) {
    graph->matrix[from][to] = weight;
}


/*
 * Floyd 算法
 *
 * dist[i][j]：
 *     顶点 i 到顶点 j 的最短距离
 *
 * next[i][j]：
 *     从 i 前往 j 的最短路径中，
 *     i 的下一个顶点
 */
void floyd(Graph graph, int dist[MAX_VERTEX][MAX_VERTEX], int next[MAX_VERTEX][MAX_VERTEX]) {
    int n = graph->vertexCount;

    /*
     * 初始化
     */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = graph->matrix[i][j];

            if (i != j && graph->matrix[i][j] != INF)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }


    /*
     * Floyd 核心
     *
     * 尝试让 k 作为 i -> j 的中间顶点
     */
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];

                    /*
                     * i -> j 的最短路径，
                     * 第一站和 i -> k 一样
                     */
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}


/*
 * 打印最短路径
 */
void printPath(int from, int to, int next[MAX_VERTEX][MAX_VERTEX]) {
    if (next[from][to] == -1) {
        printf("no path");
        return;
    }

    printf("%d", from);
    while (from != to) {
        from = next[from][to];
        printf(" -> %d", from);
    }
}


int main() {

    struct Graph graph;

    initGraph(&graph, 4);

    /*
     * 图：
     *
     * 0 --2--> 1
     * 0 --6--> 2
     *
     * 1 --3--> 2
     * 1 --1--> 3
     *
     * 2 --1--> 3
     */
    addEdge(&graph, 0, 1, 2);
    addEdge(&graph, 0, 2, 6);
    addEdge(&graph, 1, 2, 3);
    addEdge(&graph, 1, 3, 1);
    addEdge(&graph, 2, 3, 1);

    int dist[MAX_VERTEX][MAX_VERTEX];
    int next[MAX_VERTEX][MAX_VERTEX];

    floyd(&graph, dist, next);

    /*
     * 输出所有顶点之间的最短距离
     */
    printf("Shortest distance matrix:\n");
    for (int i = 0; i < graph.vertexCount; ++i) {
        for (int j = 0; j < graph.vertexCount; ++j) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }

    /*
     * 示例：打印 0 -> 3 的最短路径
     */
    printf("\n0 -> 3: distance = %d, path = ", dist[0][3]);
    printPath(0, 3, next);
    printf("\n");

    return 0;
}