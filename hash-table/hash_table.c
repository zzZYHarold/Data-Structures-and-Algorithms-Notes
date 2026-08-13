//
// Created by zyh on 2026/8/3.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
// 简单哈希表的构建

#define TABLE_SIZE 9

/* 哈希表中的元素 */
typedef struct {
    int key;
} Element;

/* 哈希表 */
typedef struct {
    Element* table[TABLE_SIZE];
} HashTable;

/* 哈希函数：根据 key 计算数组下标 */
int hash(int key) {
    return key % TABLE_SIZE;
}

/* 初始化哈希表 */
void initHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; ++i)
        hashTable->table[i] = NULL;
}

/* 插入元素，不处理哈希冲突 */
void insert(HashTable* hashTable, Element* element) {
    int index = hash(element->key);
    hashTable->table[index] = element;
}

/* 查找元素 */
bool find(const HashTable* hashTable, int key) {
    int index = hash(key);

    /* 对应位置为空，说明没有该元素 */
    if (!hashTable->table[index])
        return false;

    /* 对应位置不为空，检查 key 是否相同 */
    return hashTable->table[index]->key == key;
}

/* 创建元素 */
Element* createElement(int key) {
    Element* element = malloc(sizeof(Element));

    if (!element)
        return NULL;

    element->key = key;
    return element;
}

/* 释放哈希表中的元素 */
void destroyHashTable(HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        free(hashTable->table[i]);
        hashTable->table[i] = NULL;
    }
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);

    HashTable hashTable;
    initHashTable(&hashTable);

    insert(&hashTable, createElement(10));
    insert(&hashTable, createElement(7));
    insert(&hashTable, createElement(13));
    insert(&hashTable, createElement(29));

    printf("查找 1：%d\n", find(&hashTable, 1));
    printf("查找 13：%d\n", find(&hashTable, 13));

    destroyHashTable(&hashTable);

    return 0;
}


