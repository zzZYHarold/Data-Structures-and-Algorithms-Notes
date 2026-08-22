//
// Created by zyh on 2026/8/19.
//

#include <stdio.h>

// 快速排序 -- 冒泡排序进阶版

/*
 * 快速排序
 * arr   : 待排序数组
 * start : 当前排序区间左端点
 * end   : 当前排序区间右端点
 */

/*
    设数组长度为N，详细过程为：

    在一开始，排序范围是整个数组
    排序之前，我们选择整个排序范围内的第一个元素作为基准，对排序范围内的元素进行快速排序：
    1. 先从最右边向左看，依次将每一个元素与基准元素进行比较，如果发现比基准元素小，
    那么就与左边遍历位置上的元素（一开始是基准元素的位置）进行交换，此时保留右边当前遍历的位置。
    2. 交换后，转为从左往右开始遍历元素，如果发现比基准元素大，那么就与之前保留的右边遍历的位置上的元素进行交换，
    同样保留左边当前的位置，循环执行上一个步骤。
    3. 当左右遍历撞到一起时，本轮快速排序完成，最后在最中间的位置就是基准元素的位置了。
    以基准位置为中心，划分左右两边，以同样的方式执行快速排序。
 */
void quickSort(int arr[], int start, int end) {
    // 区间中只有 0 或 1 个元素，无需排序
    if (start >= end)
        return;

    int left = start, right = end;
    int pivot = arr[start];

    /*
    * 对当前区间进行划分：
    *
    * 最终效果：
    * [ <= pivot ] pivot [ >= pivot ]
    */
    while (left < right) {
        while (left < right && arr[right] >= pivot)
            right--;
        arr[left] = arr[right];

        while (left < right && arr[left] <= pivot)
            left++;
        arr[right] = arr[left];
    }
    /*
     * left == right
     * 此时左右指针相遇，该位置就是 pivot 的最终位置
     */
    arr[left] = pivot;

    quickSort(arr, start, left - 1);
    quickSort(arr, left + 1, end);
}

int main() {
    int arr[] = {3, 5, 7, 2, 9, 0, 6, 1, 8, 4};
    quickSort(arr, 0, sizeof(arr) / sizeof(int) - 1);

    for (int i = 0; i < 10; ++i)
        printf("%d ", arr[i]);
}
