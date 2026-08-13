//
// Created by zyh on 2026/8/11.
//

#include <stdio.h>
#include <stdbool.h>

// 优化版：路径压缩 + 按大小合并

#define SIZE 13

typedef struct {
    int parent[SIZE];
} UnionFind;


/*
 * 初始化：
 * 每个元素单独构成一个集合。
 *
 * parent[root] < 0
 * 负数绝对值表示集合大小。
 */
void initUnionFind(UnionFind* uf) {
    for (int i = 0; i < SIZE; ++i)
        uf->parent[i] = -1;
}


/*
 * Find + 路径压缩
 * 使用迭代
 */
int findRootWithIteration(UnionFind* uf, int x) {
    int root = x;

    // 第一次遍历：找到根
    while (uf->parent[root] >= 0)
        root = uf->parent[root];

    // 第二次遍历：压缩路径
    while (x != root) {
        int parent = uf->parent[x];  // 暂存原来的父结点
        uf->parent[x] = root;        // x 直接挂到根上
        x = parent;                  // 继续处理原来的父结点
    }

    return root;
}

/*
 * Find + 路径压缩
 * 使用递归
 */
int findRootWithRecursion(UnionFind* uf, int x) {
    if (uf->parent[x] < 0)
        return x;

    uf->parent[x] = findRootWithRecursion(uf, uf->parent[x]);
    return uf->parent[x];
}


/*
 * Union by Size
 * parent[root] = -size;
 * 小树挂到大树下面。
 */
void unionSet(UnionFind* uf, int a, int b) {
    int root1 = findRootWithRecursion(uf, a);
    int root2 = findRootWithRecursion(uf, b);

    if (root1 == root2)
        return;

    /*
     * 因为存的是负的 size，
     * 数值越小，实际上集合越大。
     */
    if (uf->parent[root1] <= uf->parent[root2]) {
        // 更新集合大小
        uf->parent[root1] += uf->parent[root2];

        // root2 挂到 root1
        uf->parent[root2] = root1;
    }
    else {
        // 更新集合大小
        uf->parent[root2] += uf->parent[root1];

        // root1 挂到 root2
        uf->parent[root1] = root2;
    }
}


/*
 * 判断两个元素是否属于同一个集合。
 */
bool isSameSet(UnionFind* uf, int a, int b) {
    return findRootWithRecursion(uf, a) == findRootWithRecursion(uf, b);
}