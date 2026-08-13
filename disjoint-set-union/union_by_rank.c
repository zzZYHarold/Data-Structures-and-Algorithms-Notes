//
// Created by zyh on 2026/8/11.
//

#include <stdio.h>

// 按秩合并--rank: 树高的估计值

/** 有路径压缩后，“ rank = 高度 ”就不完全准确了
*   假设原来：

    A
    |
    B
    |
    C
    rank[A] = 2

    执行路径压缩后可能变成：

        A
       / \
      B   C
    实际高度已经下降了,但rank[A]通常不会减回去
 */

#define SIZE 13

typedef struct {
    int parent[SIZE];
    int rank[SIZE];  // 需要额外维护树大概多高
} UnionFind;

void initUnionFind(UnionFind* uf) {
    for (int i = 0; i < SIZE; ++i) {
        uf->parent[i] = -1;
        uf->rank[i] = 0;
    }
}

int findRoot(UnionFind* uf, int x) {
    if (uf->parent[x] < 0)
        return x;

    uf->parent[x] = findRoot(uf, uf->parent[x]);
    return uf->parent[x];
}

void unionSet(UnionFind* uf, int a, int b) {
    int root1 = findRoot(uf, a);
    int root2 = findRoot(uf, b);

    if (root1 == root2)
        return;

    if (uf->rank[root1] < uf->rank[root2]) {
        // root1 更矮，挂到 root2
        uf->parent[root1] = root2;
    }
    else if (uf->rank[root1] > uf->rank[root2]) {
        // root2 更矮，挂到 root1
        uf->parent[root2] = root1;
    }
    else {
        /*
         * 两棵树一样高。
         *
         * 随便选一棵挂到另一棵下面，
         * 新树高度增加 1。
         */
        uf->parent[root2] = root1;
        uf->rank[root1]++;
    }
}