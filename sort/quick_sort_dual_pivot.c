//
// Created by zyh on 2026/8/19.
//

#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 *  蓝 -> 橙 -> 绿
    因为有三个区域，其中蓝色指针位置及其左边的区域都是小于基准1的，橙色指针左边到蓝色指针之间的区域都是不小于基准1且不大于基准2的，
    绿色指针位置及其右边的区域都是大于基准2的，橙色指针和绿色指针之间的区域，都是待排序区域。

    首先我们从橙色指针所指元素开始进行判断，分三种情况：
    1. 如果小于基准1，那么需要先将蓝色指针向后移，把元素交换换到蓝色指针那边去，然后橙色指针也向后移动。
    2. 如果不小于基准1且不大于基准2，那么不需要做什么，直接把橙色指针向前移动即可，因为本身就是这个范围。
    3. 如果大于基准2，先将右边指针左移，不断向前找到一个不比基准2大的，交换过去。
 */
void dualPivotQuickSort(int arr[], int start, int end) {
    if (start >= end)
        return;

    if (arr[start] > arr[end])
        swap(&arr[start], &arr[end]);

    /*
     * left  : 小于 pivot1 区域的右边界
     * mid   : 当前正在检查的元素
     * right : 大于 pivot2 区域的左边界
     */
    int left = start, right = end, mid = left + 1;
    int pivot1 = arr[left], pivot2 = arr[right];

    /*
     * 2. 将元素划分成三个区域
     *
     * < pivot1
     * pivot1 ~ pivot2
     * > pivot2
     */
    while (mid < right) {
        if (arr[mid] < pivot1)
            swap(&arr[++left], &arr[mid++]);
        else if (arr[mid] <= pivot2)
            mid++;
        else {
            // 从右往左寻找一个 <= pivot2 的元素
            while (arr[--right] > pivot2 && mid < right);
            // 未排序区域已经为空
            if (mid >= right)
                break;
            swap(&arr[mid], &arr[right]);
        }
    }
    swap(&arr[start], &arr[left]);    //最后基准1跟left交换位置，正好左边的全部比基准1小
    swap(&arr[end], &arr[right]);     //最后基准2跟right交换位置，正好右边的全部比基准2大
    /*
     * 此时数组被划分为：
     * { [ < pivot1 ] pivot1 [ pivot1 ~ pivot2 ] pivot2 [ > pivot2 ] }
     */

    //继续对三个区域再次进行双轴快速排序
    dualPivotQuickSort(arr, start, left - 1);
    dualPivotQuickSort(arr, left + 1, right - 1);
    dualPivotQuickSort(arr, right + 1, end);
}

int main() {
    int arr[] = {3, 5, 7, 2, 9, 0, 6, 1, 8, 4};
    dualPivotQuickSort(arr, 0, sizeof(arr) / sizeof(int) - 1);

    for (int i = 0; i < 10; ++i)
        printf("%d ", arr[i]);
}