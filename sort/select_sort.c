//
// Created by zyh on 2026/8/17.
//

#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectSort(int arr[], int size) {
    int left = 0, right = size - 1;  // 相当于左端和右端都是已经排好序的，中间是待排序的，所以说范围不断缩小
    while (left < right) {
        int minIndex = left, maxIndex = right;
        for (int i = left; i <= right; ++i) {
            if (arr[i] < arr[minIndex])
                minIndex = i;
            if (arr[i] > arr[maxIndex])
                maxIndex = i;
        }

        swap(&arr[right], &arr[maxIndex]);  // 这里先把大的换到右边
        // 注意大的换到右边之后，被换出来的这个有可能就是最小的
        // 此时因为已经被换出来了，所以说需要将minIndex改到换出来的那个位置，也就是maxIndex
        if (minIndex == right)
            minIndex = maxIndex;
        swap(&arr[left], &arr[minIndex]);

        left++, right--;
    }
}

int main() {
    int arr[] = {3, 5, 7, 2, 9, 0, 6, 1, 8, 4};
    selectSort(arr, sizeof(arr) / sizeof(int));

    for (int i = 0; i < 10; ++i)
        printf("%d ", arr[i]);
}