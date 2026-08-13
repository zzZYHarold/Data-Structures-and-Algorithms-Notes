//
// Created by zyh on 2026/7/30.
//

// 堆Heap -- 通常被实现为一个可以看作完全二叉树的数组对象
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <windows.h>

typedef int T;

typedef struct MaxHeap {
    T *arr;

    // 当前有效元素数量
    size_t size;

    // 最多能够存放的有效元素数量
    // arr[0] 不使用，所以实际申请 capacity + 1 个位置
    size_t capacity;
} MaxHeap;


/**
 * 初始化堆。
 *
 * initialCapacity 表示能够存放的有效元素数量，
 * 不包括未使用的 arr[0]。
 */
bool heapInit(MaxHeap* heap, size_t initialCapacity) {
    if (heap == NULL)
        return false;

    if (initialCapacity == 0)
        initialCapacity = 8;

    heap->arr = malloc((initialCapacity + 1) * sizeof(T));

    if (heap->arr == NULL) {
        heap->size = 0;
        heap->capacity = 0;
        return false;
    }

    heap->size = 0;
    heap->capacity = initialCapacity;

    return true;
}


/**
 * 释放堆占用的内存。
 */
void heapDestroy(MaxHeap* heap) {
    if (heap == NULL)
        return;

    free(heap->arr);

    heap->arr = NULL;
    heap->size = 0;
    heap->capacity = 0;
}


/**
 * 判断堆是否为空。
 */
bool heapIsEmpty(const MaxHeap* heap) {
    return heap == NULL || heap->size == 0;
}


/**
 * 扩大底层数组容量。
 */
static bool heapGrow(MaxHeap* heap) {
    size_t newCapacity;

    if (heap->capacity == 0)
        newCapacity = 1;
    else
        newCapacity = heap->capacity * 2;

    T* newArr = realloc(heap->arr, (newCapacity + 1) * sizeof(T));

    if (newArr == NULL)
        // realloc 失败时，原来的 heap->arr 仍然有效
        return false;

    heap->arr = newArr;
    heap->capacity = newCapacity;

    return true;
}


/**
 * 向大根堆中插入元素。
 */
bool heapInsert(MaxHeap* heap, T element) {
    if (heap == NULL || heap->arr == NULL)
        return false;

    // 空间不足时自动扩容
    if (heap->size == heap->capacity)
        if (!heapGrow(heap))
            return false;

    // 先在最后增加一个位置
    size_t index = ++heap->size;

    /*
     * 向上堆化：
     *
     * 如果 element 大于父结点，
     * 就把父结点向下移动。
     */
    while (index > 1 && element > heap->arr[index / 2]) {
        heap->arr[index] = heap->arr[index / 2];
        index /= 2;
    }

    // 把 element 放入最终位置
    heap->arr[index] = element;

    return true;
}


/**
 * 查看堆顶最大值，但不删除。
 */
bool heapPeekMax(const MaxHeap* heap, T* result) {
    if (heap == NULL || heap->size == 0 || result == NULL)
        return false;

    *result = heap->arr[1];

    return true;
}


/**
 * 删除并返回堆顶最大值。
 *
 * 返回 true 表示删除成功，
 * 最大值写入 result。
 */
bool heapDeleteMax(MaxHeap *heap, T *result) {
    if (heap == NULL || heap->size == 0 || result == NULL)
        return false;

    /*
    ① 删除根
        ↓
    ② 最后元素补根
        ↓
    ③ 和两个孩子中较大的比较
        ↓
    ④ 比孩子小 → 下沉
        ↓
    ⑤ 找到位置
     */

    // 保存要删除的最大值
    *result = heap->arr[1];

    // 保存最后一个元素
    T lastElement = heap->arr[heap->size];

    --heap->size;

    // 原来只有一个元素，删除后堆已经为空
    if (heap->size == 0)
        return true;

    size_t index = 1;

    /*
     * 向下堆化。
     *
     * index <= size / 2 表示 index 至少有左孩子。
     */
    while (index <= heap->size / 2) {
        size_t child = index * 2;

        /*
         * 如果右孩子存在，并且比左孩子大，
         * 就选择右孩子。
         */
        if (child < heap->size && heap->arr[child + 1] > heap->arr[child])
            ++child;

        /*
         * lastElement 已经不小于较大的孩子，
         * 说明当前位置符合大根堆规则。
         */
        if (lastElement >= heap->arr[child])
            break;

        // 把较大的孩子向上移动
        heap->arr[index] = heap->arr[child];

        // 继续检查下一层
        index = child;
    }

    // 将最后一个元素放入最终位置
    heap->arr[index] = lastElement;

    return true;
}


/**
 * 打印堆的数组表示。
 *
 * 注意：堆数组不是完全降序排列，
 * 它只保证父结点不小于孩子。
 */
void heapPrint(const MaxHeap *heap) {
    if (heap == NULL)
        return;

    for (size_t i = 1; i <= heap->size; ++i)
        printf("%d ", heap->arr[i]);

    putchar('\n');
}


int main(void) {
    SetConsoleOutputCP(CP_UTF8);

    MaxHeap heap;

    if (!heapInit(&heap, 4)) {
        fprintf(stderr, "堆初始化失败\n");
        return EXIT_FAILURE;
    }

    T elements[] = {5, 2, 3, 7, 6};
    size_t count = sizeof elements / sizeof elements[0];

    for (size_t i = 0; i < count; ++i) {
        if (!heapInsert(&heap, elements[i])) {
            fprintf(stderr, "插入元素 %d 失败\n", elements[i]);

            heapDestroy(&heap);
            return EXIT_FAILURE;
        }
    }

    printf("堆的数组表示：");
    heapPrint(&heap);

    printf("依次删除最大值：");

    T maxValue;

    while (heapDeleteMax(&heap, &maxValue))
        printf("%d ", maxValue);

    putchar('\n');

    heapDestroy(&heap);

    return EXIT_SUCCESS;
}