//
// Created by zyh on 2026/8/11.
//

#include <stdio.h>
#include <limits.h>

// 最小生成树--邻接矩阵 + Prim

/** 核心数据
    visited[i]   // i 是否已经进入生成树
    lowcost[i]   // 当前生成树连接 i 的最小代价
    closest[i]   // 这条最小边来自哪个树内顶点
 */

#define MAX_VERTEX 10
#define INF INT_MAX

typedef struct Graph {
    int vertexCount;
    int matrix[MAX_VERTEX][MAX_VERTEX];
} * Graph;

/**
 * 初始化无向带权图
 */
void initGraph(Graph graph, int vertexCount) {
    graph->vertexCount = vertexCount;

    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (i == j)
                graph->matrix[i][j] = 0;
            else
                graph->matrix[i][j] = INF;
        }
    }
}

/**
 * 添加无向边
 */
void addEdge(Graph graph, int from, int to, int weight) {
    graph->matrix[from][to] = weight;
    graph->matrix[to][from] = weight;
}

/**
 * Prim 最小生成树 :
    找最小 lowcost
          ↓
    加入这个顶点
          ↓
    利用新顶点更新 lowcost
          ↓
    重复
 */
void prim(Graph graph, int start) {
    int visited[MAX_VERTEX] = {0};

    // lowcost[i]：
    // 当前生成树连接顶点 i 的最小边权
    int lowcost[MAX_VERTEX];

    // closest[i]：
    // 当前应该从哪个树内顶点连接到 i
    int closest[MAX_VERTEX];

    int totalWeight = 0;

    /*
     * 一开始生成树中只有 start。
     *
     * 所以每个顶点与生成树之间的最小距离，
     * 就是 start 到它的边权。
     */
    for (int i = 0; i < graph->vertexCount; ++i) {
        lowcost[i] = graph->matrix[start][i];
        closest[i] = start;
    }

    visited[start] = 1;
    lowcost[start] = 0;

    /*
     * 已经有 start 一个顶点，
     * 因此还需要加入 vertexCount - 1 个顶点。
     */
    for (int i = 1; i < graph->vertexCount; ++i) {

        /*
         * 第一步：
         * 从所有“树外顶点”中，
         * 找 lowcost 最小的顶点。
         */
        int min = INF;
        int k = -1;

        for (int j = 0; j < graph->vertexCount; ++j) {
            if (!visited[j] && lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
        }

        /*
         * 找不到可以连接的新顶点，
         * 说明原图不连通。
         */
        if (k == -1) {
            printf("图不连通，不存在生成树\n");
            return;
        }

        /*
         * closest[k] ---- k
         *
         * 就是这一次加入 MST 的边。
         */
        printf("%d -- %d  weight = %d\n",
               closest[k], k, lowcost[k]);

        totalWeight += lowcost[k];

        /*
         * k 正式进入生成树。
         */
        visited[k] = 1;

        /*
         * 第二步：
         * 因为 k 新加入了生成树，
         * 看看通过 k 能不能以更小代价连接其他树外顶点。
         */
        for (int j = 0; j < graph->vertexCount; ++j) {

            if (!visited[j] && graph->matrix[k][j] < lowcost[j]) {
                lowcost[j] = graph->matrix[k][j];
                closest[j] = k;
            }
        }
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

    prim(&graph, 0);

    return 0;
}