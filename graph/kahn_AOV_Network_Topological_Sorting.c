//
// Created by zyh on 2026/8/13.
//

#include <stdio.h>
#include <stdlib.h>

// 拓扑排序--邻接表 + Kahn

#define MAX_VERTEX 100

/*
 * 邻接表中的边结点
 *
 * 例如：
 * A -> B
 * 那么 A 的邻接链表中会有一个 to = B 的结点
 */
typedef struct EdgeNode {
    int to;
    struct EdgeNode* next;
} * Edge;


/*
 * 图
 * adj[i]：
 * 顶点 i 的邻接链表
 */
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
 * from -> to
 */
void addEdge(Graph graph, int from, int to) {
    Edge edge = malloc(sizeof(struct EdgeNode));

    if (!edge)
        return;

    edge->to = to;

    /*
     * 头插法
     */
    edge->next = graph->adj[from];
    graph->adj[from] = edge;
}


/*
 * Kahn 算法实现拓扑排序
 *
 * result[]：
 * 保存最终的拓扑序列
 *
 * 返回：
 * 1 -> 拓扑排序成功，图是 DAG
 * 0 -> 图中存在环
 */
_Bool topologicalSort(Graph graph, int result[]) {
    int indegree[MAX_VERTEX] = {0};

    /*
     * 1. 统计每个顶点的入度-
     * 遍历所有边：
     * u -> v
     * 则：
     * indegree[v]++
     */
    for (int u = 0; u < graph->vertexCount; ++u) {
        Edge edge = graph->adj[u];
        while (edge) {
            indegree[edge->to]++;
            edge = edge->next;
        }
    }

    /*
     * 2. 创建队列
     *
     * 为了突出拓扑排序本身，
     * 这里先直接使用数组模拟队列
     */
    int queue[MAX_VERTEX];
    int front = 0;
    int rear = 0;

    /*
     * 所有入度为 0 的顶点入队
     */
    for (int i = 0; i < graph->vertexCount; ++i)
        if (indegree[i] == 0)
            queue[rear++] = i;

    /*
     * 已经排入拓扑序列的顶点数量
     */
    int count = 0;

    /*
     * 3. 不断处理入度为 0 的顶点
     */
    while (front < rear) {
        // 出队
        int u = queue[front++];

        // u 加入拓扑序列
        result[count++] = u;

        /*
         * 遍历 u 的所有出边：
         * u -> v
         */
        Edge edge = graph->adj[u];
        while (edge) {
            int v = edge->to;

            /*
             * 相当于删除：
             * u -> v
             * 所以 v 的入度减 1
             */
            indegree[v]--;

            /*
             * 如果 v 的所有前置顶点都已经处理完，
             * v 就可以入队
             */
            if (indegree[v] == 0)
                queue[rear++] = v;

            edge = edge->next;
        }
    }

    /*
     * 所有顶点都进入拓扑序：
     * 说明图中没有环
     * 否则说明存在环
     */
    return count == graph->vertexCount;
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
        graph->adj[i] = NULL;
    }
}


int main() {
    struct Graph graph;
    initGraph(&graph, 10);

    /*
     * 顶点：
     *
     * 0 1 2 3 4 5 6 7 8 9
     * A B C D E F G H I J
     *
     *
     * A -> B
     * A -> C
     * A -> D
     *
     * B -> E
     * B -> G
     *
     * C -> E
     * C -> F
     *
     * D -> F
     *
     * E -> G
     * E -> H
     *
     * F -> H
     * F -> I
     *
     * G -> J
     * H -> J
     * I -> J
     */

    addEdge(&graph, 0, 1);    // A -> B
    addEdge(&graph, 0, 2);    // A -> C
    addEdge(&graph, 0, 3);    // A -> D
    addEdge(&graph, 1, 4);    // B -> E
    addEdge(&graph, 1, 6);    // B -> G
    addEdge(&graph, 2, 4);    // C -> E
    addEdge(&graph, 2, 5);    // C -> F
    addEdge(&graph, 3, 5);    // D -> F
    addEdge(&graph, 4, 6);    // E -> G
    addEdge(&graph, 4, 7);    // E -> H
    addEdge(&graph, 5, 7);    // F -> H
    addEdge(&graph, 5, 8);    // F -> I
    addEdge(&graph, 6, 9);    // G -> J
    addEdge(&graph, 7, 9);    // H -> J
    addEdge(&graph, 8, 9);    // I -> J

    int result[MAX_VERTEX];

    if (topologicalSort(&graph, result)) {
        printf("Topological Order: ");
        for (int i = 0; i < graph.vertexCount; ++i)
            printf("%c ", result[i] + 'A');
        printf("\n");
    }
    else {
        printf("The graph contains a cycle.\n");
    }

    destroyGraph(&graph);
    return 0;
}