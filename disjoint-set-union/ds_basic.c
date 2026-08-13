//
// Created by zyh on 2026/8/11.
//

#include <stdio.h>
#include <windows.h>

// 最基础、最适合理解并查集原理的 C 实现
// 核心思想只有一句：用一个 parent[] 数组表示若干棵树；每棵树代表一个集合，根结点代表这个集合

#define SIZE 13

typedef struct {
    int parent[SIZE];
} UnionFind;


/*
 * 初始化：
 * 每个元素一开始各自构成一个集合。
 *
 * parent[i] == -1 表示 i 是一个集合的根结点。
 */
void initUnionFind(UnionFind* uf) {
    for (int i = 0; i < SIZE; ++i)
        uf->parent[i] = -1;
}


/*
 * Find：
 * 查找元素 x 所属集合的根结点。
 *
 * 如果 parent[x] >= 0，
 * 说明 x 还有父结点，就不断向上寻找。
 */
int findRoot(const UnionFind* uf, int x) {
    while (uf->parent[x] >= 0)
        x = uf->parent[x];

    return x;
}


/*
 * Union：
 * 将 root2 所在的集合合并到 root1 所在的集合。
 *
 * 注意：
 * 这里传进来的必须是两个集合的根结点。
 */
void unionRoots(UnionFind* uf, int root1, int root2) {
    if (root1 == root2)
        return;

    uf->parent[root2] = root1;
}


/*
 * 更方便的封装：
 *
 * 用户直接传两个普通元素 a、b，
 * 函数内部先找到各自的根，然后再合并。
 */
void unionSet(UnionFind* uf, int a, int b) {
    int root1 = findRoot(uf, a);
    int root2 = findRoot(uf, b);

    unionRoots(uf, root1, root2);
}


/*
 * 判断两个元素是否属于同一个集合。
 */
_Bool isSameSet(const UnionFind* uf, int a, int b) {
    return findRoot(uf, a) == findRoot(uf, b);
}


/*
 * 打印 parent 数组，方便观察。
 */
void printUnionFind(const UnionFind* uf) {
    printf("index : ");
    for (int i = 0; i < SIZE; ++i)
        printf("%3d", i);

    printf("\nparent: ");
    for (int i = 0; i < SIZE; ++i)
        printf("%3d", uf->parent[i]);

    printf("\n");
}


int main(void) {
    SetConsoleOutputCP(65001);

    UnionFind uf;
    initUnionFind(&uf);

    /*
     * 假设：
     *
     * 0 -> A
     * 1 -> B
     * 2 -> C
     * ...
     * 12 -> M
     */

    unionSet(&uf, 0, 1);   // A、B 合并
    unionSet(&uf, 1, 4);   // B、E 合并
    unionSet(&uf, 1, 5);   // B、F 合并
    unionSet(&uf, 4, 10);  // E、K 合并
    unionSet(&uf, 4, 11);  // E、L 合并
    unionSet(&uf, 2, 6);   // C、G 合并
    unionSet(&uf, 3, 7);   // D、H 合并
    unionSet(&uf, 3, 8);   // D、I 合并
    unionSet(&uf, 3, 9);   // D、J 合并
    unionSet(&uf, 7, 12);  // H、M 合并

    printUnionFind(&uf);

    printf("K 和 F 是否属于同一集合：%d\n",
           isSameSet(&uf, 10, 5));

    printf("G 和 J 是否属于同一集合：%d\n",
           isSameSet(&uf, 6, 9));

    printf("J 所属集合的根：%d\n",
           findRoot(&uf, 9));

    return 0;
}