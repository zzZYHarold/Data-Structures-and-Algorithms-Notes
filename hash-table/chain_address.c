//
// Created by zyh on 2026/8/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 链地址法

#define SIZE 9

// 链表结点
typedef struct ListNode {
    int key;
    struct ListNode* next;
} ListNode;

// 哈希表
typedef struct {
    ListNode** table;     // 指针数组，每个元素指向一条链表
} HashTable;


/**
 * 哈希函数
 */
int hash(int key) {
    int hashCode = key % SIZE;

    // 防止负数 key 得到负下标
    return hashCode >= 0 ? hashCode : hashCode + SIZE;
}


/**
 * 初始化哈希表
 */
bool init(HashTable* hashTable) {
    if (hashTable == NULL)
        return false;

    /*
     * 分配 SIZE 个 ListNode* 的空间。
     *
     * calloc 会把所有元素初始化为 NULL，
     * 表示每个位置上的链表一开始都是空的。
     */
    hashTable->table = calloc(SIZE, sizeof(ListNode*));
    return hashTable->table != NULL;
}


/**
 * 创建链表结点
 */
ListNode* createNode(int key) {
    ListNode* node = malloc(sizeof(ListNode));

    if (node == NULL)
        return NULL;

    node->key = key;
    node->next = NULL;

    return node;
}


/**
 * 插入元素
 */
bool insert(HashTable* hashTable, int key) {
    if (hashTable == NULL || hashTable->table == NULL)
        return false;

    int hashCode = hash(key);

    ListNode *node = createNode(key);

    if (node == NULL)
        return false;

    /*
     * 使用头插法：
     *
     * 新结点指向原来的第一个结点，
     * 然后让数组中的头指针指向新结点。
     *
     * 时间复杂度为 O(1)。
     */
    node->next = hashTable->table[hashCode];
    hashTable->table[hashCode] = node;

    return true;
}


/**
 * 查找元素
 */
bool find(const HashTable* hashTable, int key) {
    if (hashTable == NULL || hashTable->table == NULL)
        return false;

    int hashCode = hash(key);

    ListNode* curr = hashTable->table[hashCode];

    while (curr != NULL) {
        if (curr->key == key)
            return true;

        curr = curr->next;
    }

    return false;
}


/**
 * 打印哈希表
 */
void printHashTable(const HashTable* hashTable) {
    if (hashTable == NULL || hashTable->table == NULL)
        return;

    for (int i = 0; i < SIZE; ++i) {
        printf("[%d]", i);

        ListNode* curr = hashTable->table[i];

        while (curr != NULL) {
            printf(" -> %d", curr->key);
            curr = curr->next;
        }

        printf(" -> NULL\n");
    }
}


/**
 * 释放哈希表
 */
void destroy(HashTable* hashTable) {
    if (hashTable == NULL || hashTable->table == NULL)
        return;

    for (int i = 0; i < SIZE; ++i) {
        ListNode* curr = hashTable->table[i];

        while (curr != NULL) {
            ListNode* next = curr->next;
            free(curr);
            curr = next;
        }
    }

    free(hashTable->table);
    hashTable->table = NULL;
}


int main(void) {
    HashTable hashTable;

    if (!init(&hashTable)) {
        printf("哈希表初始化失败\n");
        return 1;
    }

    insert(&hashTable, 10);
    insert(&hashTable, 19);
    insert(&hashTable, 28);
    insert(&hashTable, 5);
    insert(&hashTable, 14);

    printHashTable(&hashTable);

    printf("\nfind 19: %s\n",
           find(&hashTable, 19) ? "true" : "false");

    printf("find 20: %s\n",
           find(&hashTable, 20) ? "true" : "false");

    destroy(&hashTable);

    return 0;
}