//
// Created by zyh on 2026/8/21.
//

#include <stdio.h>

/*  堆排序--升序：
    ① 将无序数组自底向上调整成大根堆。
    ② 大根堆的根结点 arr[0] 是当前最大元素。
    ③ 将堆顶与未排序区域的最后一个元素交换，使最大元素归位。
    ④ 缩小堆的范围，对根结点重新下滤，重复直到堆只剩一个元素。
 */

/*  Base0的完全二叉树：
    左孩子 = 2 * i + 1
    右孩子 = 2 * i + 2
    父结点 = (i - 1) / 2
 */

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * 堆化：将以 start 为根的子树调整为大根堆
 *
 * 前提：
 * start 的左右子树本身已经是大根堆
 *
 * end：
 * 当前堆的最后一个元素下标
 */
void heapify(int arr[], int start, int end) {
    // 只要存在左孩子，就说明当前结点还可能需要向下调整
    while (start * 2 + 1 <= end) {
        // 指向左孩子节点
        int child = start * 2 + 1;
        /*
         * 如果右孩子存在，并且右孩子更大，则选择右孩子
         * 最终 child 指向两个孩子中较大的那个
         */
        if (child + 1 <= end && arr[child + 1] > arr[child])
            child++;

        // 如果较大的孩子仍然比父结点大，不满足大根堆性质
        if (arr[child] > arr[start]) {
            swap(&arr[start], &arr[child]);
            // 原来的父结点已经被换到下面，继续向下检查
            start = child;
        }
        else {
            // 父结点已经 >= 两个孩子，整棵子树已经满足大根堆性质
            break;
        }
    }
}

void heapSort(int arr[], int size) {
    /*
    * 第一阶段：建立大根堆
    * size / 2 - 1 是最后一个非叶子结点。从后向前依次进行堆化。
    */
    for (int i = size / 2 - 1; i >= 0; --i)
        heapify(arr, i, size - 1);

    /*
     * 第二阶段：排序
     * 每次将堆顶最大值放到数组末尾，然后缩小堆的范围并重新堆化。
     */
    for (int i = size - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        heapify(arr, 0, i - 1);
    }
}

int main() {
    int arr[] = {3, 5, 7, 2, 9, 0, 6, 1, 8, 4};
    heapSort(arr, sizeof(arr) / sizeof(int));

    for (int i = 0; i < 10; ++i)
        printf("%d ", arr[i]);
}