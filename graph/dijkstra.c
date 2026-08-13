//
// Created by zyh on 2026/8/12.
//

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// 单源最短路径--Dijkstra算法

/** 最核心就是三个东西：
  * dist[] 目前已知的从起点 start 到顶点 i 的最短距离
    visited[] 这个顶点的最短距离已经正式确定，以后不会再改变
    prev[] 用来恢复最短路径
 */

#define MAX_VERTEX 100
#define INF (INT_MAX / 2)

/*
 * 带权图 —— 邻接矩阵
 *
 * matrix[i][j]：
 *   INF -> i 到 j 没有边
 *   其他值 -> 边 i -> j 的权值
 */
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
 * Dijkstra 单源最短路径
 *
 * dist[i]:
 *     起点 start 到顶点 i 的最短距离
 *
 * prev[i]:
 *     最短路径上，顶点 i 的前驱顶点
 */
void dijkstra(Graph graph, int start, int dist[], int prev[]) {
    bool visited[MAX_VERTEX] = {0};

    /*
     * 初始化
     */
    for (int i = 0; i < graph->vertexCount; ++i) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    /*
     * 每轮确定一个顶点的最短距离
     */
    while (1) {
        /*
         * 1. 从尚未确定的顶点中，
         *    找 dist 最小的顶点u
         */
        int u = -1;
        int minDist = INF;

        for (int j = 0; j < graph->vertexCount; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        /*
         * 剩余顶点全部不可达
         */
        if (u == -1)
            break;

        /*
         * 2. u 的最短距离正式确定
         */
        visited[u] = true;

        /*
         * 3. 利用 u 尝试更新其他顶点
         *
         * start ---> u ---> v
         */
        for (int v = 0; v < graph->vertexCount; ++v)
            if (!visited[v] && graph->matrix[u][v] != INF && dist[u] + graph->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->matrix[u][v];

                /*
                 * v 的最短路径现在经过 u
                 */
                prev[v] = u;
            }
    }
}


/*
 * 根据 prev[] 打印最短路径
 */
void printPath(int prev[], int vertex) {
    if (vertex == -1)
        return;

    printPath(prev, prev[vertex]);
    printf("%d ", vertex);
}


int main() {
    struct Graph graph;

    initGraph(&graph, 5);

    /*
     * 建立有向带权图
     *
     * 0 --10--> 1
     * 0 --5---> 4
     *
     * 1 --1---> 2
     * 1 --2---> 4
     *
     * 2 --4---> 3
     *
     * 3 --7---> 0
     * 3 --6---> 2
     *
     * 4 --3---> 1
     * 4 --9---> 2
     * 4 --2---> 3
     */
    addEdge(&graph, 0, 1, 10);
    addEdge(&graph, 0, 4, 5);
    addEdge(&graph, 1, 2, 1);
    addEdge(&graph, 1, 4, 2);
    addEdge(&graph, 2, 3, 4);
    addEdge(&graph, 3, 0, 7);
    addEdge(&graph, 3, 2, 6);
    addEdge(&graph, 4, 1, 3);
    addEdge(&graph, 4, 2, 9);
    addEdge(&graph, 4, 3, 2);

    int dist[MAX_VERTEX];
    int prev[MAX_VERTEX];
    int start = 0;

    dijkstra(&graph, start, dist, prev);

    for (int i = 0; i < graph.vertexCount; ++i) {
        printf("%d -> %d: ", start, i);

        if (dist[i] == INF) {
            printf("unreachable\n");
            continue;
        }

        printf("distance = %d, path = ", dist[i]);
        printPath(prev, i);
        printf("\n");
    }

    return 0;
}