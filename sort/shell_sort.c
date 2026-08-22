//
// Created by zyh on 2026/8/21.
//

#include <stdio.h>

// 希尔排序 -- 插入排序进阶版

/*
    设数组长度为N，详细过程为：

    首先求出最初的步长，n/2即可。
    我们将整个数组按照步长进行分组，也就是两两一组（如果n为奇数的话，第一组会有三个元素）
    我们分别在这些分组内进行插入排序。
    排序完成后，我们将步长/2，重新分组，重复上述步骤，直到步长为1时，插入排序最后一遍结束。
 */
void shellSort(int arr[], int size) {
    // gap 表示当前分组的间隔/步长
    int gap = size / 2;
    while (gap >= 1) {
        // 对当前 gap 下的所有分组执行插入排序
        // 前 gap 个元素分别是各组的第一个元素，可以认为每组的第一个元素已经有序
        for (int i = gap; i < size; ++i) {
            // 当前待插入元素及其位置
            int temp = arr[i], j = i;

            // 与同一组中前面的元素比较
            // 普通插入排序是 j - 1，希尔排序则是 j - gap
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            // 找到合适位置后插入
            arr[j] = temp;
        }
        gap /= 2;
    }
}

int main() {
    int arr[] = {3, 5, 7, 2, 9, 0, 6, 1, 8, 4};
    shellSort(arr, sizeof(arr) / sizeof(int));

    for (int i = 0; i < 10; ++i)
        printf("%d ", arr[i]);
}
