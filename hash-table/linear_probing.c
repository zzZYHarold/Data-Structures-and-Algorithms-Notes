//
// Created by zyh on 2026/8/3.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// 线性探测法

#define TABLE_SIZE 9

typedef struct {
    int key;
} Element;

/* 每个槽位可能处于三种状态 */
typedef enum {
    EMPTY,       // 从未使用
    OCCUPIED,    // 当前存有元素
    DELETED      // 元素已删除
} SlotState;

typedef struct {
    Element* table[TABLE_SIZE];
    SlotState state[TABLE_SIZE];
} HashTable;


/* 哈希函数 */
int hash(int key) {
    int index = key % TABLE_SIZE;

    /* 兼容负数 key */
    if (index < 0)
        index += TABLE_SIZE;

    return index;
}


/* 初始化 */
void initHashTable(HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashTable->table[i] = NULL;
        hashTable->state[i] = EMPTY;
    }
}


/* 创建元素 */
Element* createElement(int key) {
    Element* element = malloc(sizeof (Element));

    if (element == NULL)
        return NULL;

    element->key = key;
    return element;
}


/*
 * 插入元素
 *
 * true：插入成功
 * false：元素重复或哈希表已满
 */
// 同时正确处理删除槽位复用和禁止重复 key
bool insert(HashTable* hashTable, Element* element) {
    int startIndex = hash(element->key);

    /*
     * 记录探测过程中遇到的第一个 DELETED 位置。
     * 如果最终确定元素不存在，可以复用这个位置。
     */
    int firstDeleted = -1;

    for (int step = 0; step < TABLE_SIZE; ++step) {
        int index = (startIndex + step) % TABLE_SIZE;

        // 先检查是不是重复元素
        if (hashTable->state[index] == OCCUPIED) {
            /* 不插入重复 key */
            if (hashTable->table[index]->key == element->key)
                return false;
            continue;
        }

        // 说明这个位置以前有元素，但已被删除。这个位置以后可以重新使用，但是当前代码不会立即插入
        if (hashTable->state[index] == DELETED) {
            if (firstDeleted == -1)
                firstDeleted = index;  // 如果之前还没有遇到过删除位置，就记录当前下标

            /*
             * 暂时不立即插入，因为相同的 key
             * 可能还存在于探测序列后面。
             */
            continue;
        }

        /*
         * 遇到 EMPTY，说明后面不可能还有相同元素。
         * 优先复用之前遇到的 DELETED 位置。
         */
        if (firstDeleted != -1)
            index = firstDeleted;

        hashTable->table[index] = element;
        hashTable->state[index] = OCCUPIED;

        return true;
    }

    /*
     * 如果检查了一整圈，没有 EMPTY，
     * 但存在 DELETED，也可以插入。
     */
    if (firstDeleted != -1) {
        hashTable->table[firstDeleted] = element;
        hashTable->state[firstDeleted] = OCCUPIED;

        return true;
    }

    return false;
}


/* 查找元素 */
bool find(const HashTable* hashTable, int key) {
    int startIndex = hash(key);

    for (int step = 0; step < TABLE_SIZE; ++step) {
        int index = (startIndex + step) % TABLE_SIZE;

        /*
         * EMPTY 表示这个位置从来没有使用过。
         * 探测链到这里就真正结束了。
         */
        if (hashTable->state[index] == EMPTY)
            return false;

        /*
         * 只有 OCCUPIED 状态才可以访问元素。
         *
         * 遇到 DELETED 时什么也不做，
         * 继续检查下一个位置。
         */
        if (hashTable->state[index] == OCCUPIED && hashTable->table[index]->key == key)
            return true;
    }

    return false;
}


/* 删除元素 */
bool deleteKey(HashTable* hashTable, int key) {
    int startIndex = hash(key);

    for (int step = 0; step < TABLE_SIZE; ++step) {
        int index = (startIndex + step) % TABLE_SIZE;

        /* 遇到真正的空位，说明元素不存在 */
        if (hashTable->state[index] == EMPTY)
            return false;

        if (hashTable->state[index] == OCCUPIED && hashTable->table[index]->key == key) {
            free(hashTable->table[index]);

            hashTable->table[index] = NULL;

            /*
             * 不能改成 EMPTY，
             * 必须留下 DELETED 标记。
             */
            hashTable->state[index] = DELETED;

            return true;
        }
    }

    return false;
}


/* 打印哈希表 */
void printHashTable(const HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("[%d] ", i);

        if (hashTable->state[i] == EMPTY)
            printf("EMPTY\n");
        else if (hashTable->state[i] == DELETED)
            printf("DELETED\n");
        else
            printf("%d\n", hashTable->table[i]->key);
    }
}


/* 释放哈希表 */
void destroyHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (hashTable->state[i] == OCCUPIED)
            free(hashTable->table[i]);

        hashTable->table[i] = NULL;
        hashTable->state[i] = EMPTY;
    }
}


int main(void) {
    SetConsoleOutputCP(CP_UTF8);

    HashTable hashTable;
    initHashTable(&hashTable);

    int keys[] = {0, 18, 27, 36, 45, 54, 63, 72, 81};
    int count = sizeof keys / sizeof keys[0];

    for (int i = 0; i < count; ++i) {
        Element *element = createElement(keys[i]);

        if (element == NULL) {
            printf("内存分配失败\n");
            destroyHashTable(&hashTable);
            return 1;
        }

        if (!insert(&hashTable, element)) {
            printf("插入 %d 失败\n", keys[i]);
            free(element);
        }
    }

    printf("删除 45：%d\n", deleteKey(&hashTable, 45));

    printf("查找 45：%d\n", find(&hashTable, 45));
    printf("查找 54：%d\n", find(&hashTable, 54));

    printHashTable(&hashTable);

    destroyHashTable(&hashTable);

    return 0;
}