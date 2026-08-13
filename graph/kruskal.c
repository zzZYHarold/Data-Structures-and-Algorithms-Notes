//
// Created by zyh on 2026/8/11.
//

#include <stdio.h>

// 最小生成树--边数组 + 并查集 + Kruskal

#define MAX_VERTEX 10
#define MAX_EDGE 20

// 全图有哪些边？每条边多少权重？
typedef struct Edge {
    int from;
    int to;
    int weight;
} Edge;

typedef struct Graph {
    int vertexCount;
    int edgeCount;

    Edge edges[MAX_EDGE];
} * Graph;


/* =========================
 *       图的基本操作
 * ========================= */

void initGraph(Graph graph, int vertexCount) {
    graph->vertexCount = vertexCount;
    graph->edgeCount = 0;
}

void addEdge(Graph graph, int from, int to, int weight) {
    graph->edges[graph->edgeCount].from = from;
    graph->edges[graph->edgeCount].to = to;
    graph->edges[graph->edgeCount].weight = weight;

    graph->edgeCount++;
}


/* =========================
 *          排序
 * ========================= */

/**
 * 将所有边按照权值从小到大排序。
 *
 * 这里暂时用最简单的选择排序，
 * 避免 qsort 干扰我们理解 Kruskal。
 */
void sortEdges(Graph graph) {
    for (int i = 0; i < graph->edgeCount - 1; ++i) {
        int min = i;

        for (int j = i + 1; j < graph->edgeCount; ++j)
            if (graph->edges[j].weight < graph->edges[min].weight)
                min = j;

        if (min != i) {
            Edge temp = graph->edges[i];
            graph->edges[i] = graph->edges[min];
            graph->edges[min] = temp;
        }
    }
}


/* =========================
 *          并查集
 * ========================= */

int parent[MAX_VERTEX];

/**
 * 初始化：
 *
 * 每个顶点一开始自己是一个集合。
 *
 * 0  1  2  3  4  5
 * ↓  ↓  ↓  ↓  ↓  ↓
 * 0  1  2  3  4  5
 */
void initSet(int vertexCount) {
    for (int i = 0; i < vertexCount; ++i)
        parent[i] = i;
}

/**
 * 找到 x 所属集合的根。
 */
int find(int x) {
    if (parent[x] == x)
        return x;

    return find(parent[x]);
}

/**
 * 合并 a、b 所在的两个集合。
 */
void unionSet(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);

    parent[rootA] = rootB;
}


/* =========================
 *         Kruskal
 * ========================= */

void kruskal(Graph graph) {
    /*
     * 1. 所有边按权值排序
     */
    sortEdges(graph);

    /*
     * 2. 初始化并查集
     */
    initSet(graph->vertexCount);

    int selected = 0;
    int totalWeight = 0;

    /*
     * 3. 从最小边开始依次检查
     */
    for (int i = 0; i < graph->edgeCount && selected < graph->vertexCount - 1; ++i) {
        Edge edge = graph->edges[i];

        /*
         * 两个端点不属于同一个集合：
         *
         * 加这条边不会成环。
         */
        if (find(edge.from) != find(edge.to)) {
            printf("%d -- %d  weight = %d\n", edge.from, edge.to, edge.weight);

            /*
             * 选中这条边以后，
             * 两个连通分量合并。
             */
            unionSet(edge.from, edge.to);

            totalWeight += edge.weight;
            selected++;
        }
    }

    /*
     * 正常生成树应该正好选 n-1 条边。
     */
    if (selected != graph->vertexCount - 1) {
        printf("图不连通，不存在生成树\n");
        return;
    }

    printf("MST total weight = %d\n", totalWeight);
}

int main() {
    struct Graph graph;

    initGraph(&graph, 6);

    addEdge(&graph, 0, 1, 2);   // A-B
    addEdge(&graph, 0, 2, 3);   // A-C
    addEdge(&graph, 0, 3, 1);   // A-D
    addEdge(&graph, 1, 4, 4);   // B-E
    addEdge(&graph, 1, 5, 5);   // B-F
    addEdge(&graph, 2, 3, 6);   // C-D
    addEdge(&graph, 3, 4, 2);   // D-E
    addEdge(&graph, 4, 5, 3);   // E-F

    kruskal(&graph);

    return 0;
}