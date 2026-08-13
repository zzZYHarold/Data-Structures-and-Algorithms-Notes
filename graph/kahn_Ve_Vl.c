//
// Created by zyh on 2026/8/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/** 关键路径计算
 *  Ve[v]=max(Ve[v], Ve[u]+w)
 *  Vl[u]=min(Vl[u], Vl[v]−w)
 */

#define MAX_VERTEX 100
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// 边结点
// 继续沿用前面的邻接表，只不过现在边需要多存一个 weight，表示活动耗时
typedef struct EdgeNode {
    int to;                     // 终点
    int weight;                 // 活动耗时
    struct EdgeNode *next;
} * Edge;


// AOE 图
typedef struct Graph {
    int vertexCount;
    Edge adj[MAX_VERTEX];
} * Graph;


/*
 * 初始化图
 */
void initGraph(Graph graph, int vertexCount) {
    graph->vertexCount = vertexCount;

    for (int i = 0; i < vertexCount; ++i)
        graph->adj[i] = NULL;
}


/*
 * 添加有向边
 * from ──weight──> to
 */
void addEdge(Graph graph, int from, int to, int weight) {
    Edge edge = malloc(sizeof(struct EdgeNode));
    if (!edge)
        return;

    edge->to = to;
    edge->weight = weight;

    // 头插法
    edge->next = graph->adj[from];
    graph->adj[from] = edge;
}


/*
 * 计算事件的：
 *
 * Ve：最早发生时间
 * Vl：最晚发生时间
 *
 * 返回：
 * 1 -> 成功，图是 DAG
 * 0 -> 图中存在环
 */
_Bool calculateTime(Graph graph, int Ve[], int Vl[]) {
    int indegree[MAX_VERTEX] = {0};

    /*
     * topo 保存拓扑序
     * 后面计算 Vl 时需要反向遍历拓扑序
     */
    int topo[MAX_VERTEX];
    int queue[MAX_VERTEX];
    int front = 0;
    int rear = 0;

    // ---------------------------
    // 1. 计算所有顶点的入度
    // ---------------------------
    for (int u = 0; u < graph->vertexCount; ++u) {
        Edge edge = graph->adj[u];
        while (edge) {
            indegree[edge->to]++;
            edge = edge->next;
        }
    }

    // ---------------------------
    // 2. 所有入度为 0 的顶点入队
    // ---------------------------
    for (int i = 0; i < graph->vertexCount; ++i) {
        Ve[i] = 0;
        if (indegree[i] == 0)
            queue[rear++] = i;
    }

    // ---------------------------
    // 3. Kahn 拓扑排序
    //    同时正向计算 Ve
    // ---------------------------
    int count = 0;
    while (front < rear) {
        int u = queue[front++];
        topo[count++] = u;

        /*
         * 遍历：
         * u ──w──> v
         */
        Edge edge = graph->adj[u];
        while (edge) {
            int v = edge->to;
            int w = edge->weight;

            /*
             * 计算 v 的最早发生时间
             *
             * v 可能有多个前驱，
             * 必须等最慢的那个完成。
             */
            Ve[v] = max(Ve[v], Ve[u] + w);

            // Kahn 算法
            indegree[v]--;
            if (indegree[v] == 0)
                queue[rear++] = v;

            edge = edge->next;
        }
    }

    /*
     * 没有全部进入拓扑序：
     * 图中存在环
     */
    if (count != graph->vertexCount)
        return 0;

    // ---------------------------
    // 4. 求整个工程的最短工期
    // ---------------------------
    int projectTime = 0;
    for (int i = 0; i < graph->vertexCount; ++i)
        projectTime = max(projectTime, Ve[i]);

    // ---------------------------
    // 5. 初始化 Vl
    // ---------------------------
    for (int i = 0; i < graph->vertexCount; ++i)
        Vl[i] = projectTime;

    // ---------------------------
    // 6. 按逆拓扑序计算 Vl
    // ---------------------------
    for (int i = graph->vertexCount - 1; i >= 0; --i) {
        int u = topo[i];
        Edge edge = graph->adj[u];
        while (edge) {
            int v = edge->to;
            int w = edge->weight;

            /*
             * u ──w──> v
             *
             * 要保证 v 最晚在 Vl[v] 时刻发生，
             * 那么 u 最迟必须在：
             * Vl[v] - w
             * 时刻发生。
             */
            Vl[u] = min(Vl[u], Vl[v] - w);

            edge = edge->next;
        }
    }
    return 1;
}


/*
 * 释放邻接表
 */
void destroyGraph(Graph graph) {
    for (int i = 0; i < graph->vertexCount; ++i) {
        Edge edge = graph->adj[i];
        while (edge) {
            Edge temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
}


int main() {
    struct Graph graph;
    initGraph(&graph, 6);

    /*
     * 顶点：
     *
     * 0 1 2 3 4 5
     * A B C D E F
     *
     *
     *          3
     *      A ────→ B ──3──→ E
     *      │       │         │
     *      │       2         1
     *      2       ↓         ↓
     *      ↓       D ──2───→ F
     *      C ─4──→ ↑         ↑
     *      └─────────3───────┘
     */
    addEdge(&graph, 0, 1, 3);   // A -> B
    addEdge(&graph, 0, 2, 2);   // A -> C
    addEdge(&graph, 1, 4, 3);   // B -> E
    addEdge(&graph, 1, 3, 2);   // B -> D
    addEdge(&graph, 2, 3, 4);   // C -> D
    addEdge(&graph, 2, 5, 3);   // C -> F
    addEdge(&graph, 3, 5, 2);   // D -> F
    addEdge(&graph, 4, 5, 1);   // E -> F

    int Ve[MAX_VERTEX];
    int Vl[MAX_VERTEX];

    if (!calculateTime(&graph, Ve, Vl)) {
        printf("The graph contains a cycle.\n");
    }
    else {
        printf("Vertex: ");
        for (int i = 0; i < graph.vertexCount; ++i)
            printf("%c ", 'A' + i);

        printf("\n");

        printf("Ve:     ");
        for (int i = 0; i < graph.vertexCount; ++i)
            printf("%d ", Ve[i]);

        printf("\n");

        printf("Vl:     ");
        for (int i = 0; i < graph.vertexCount; ++i)
            printf("%d ", Vl[i]);

        printf("\n");
    }

    destroyGraph(&graph);
    return 0;
}