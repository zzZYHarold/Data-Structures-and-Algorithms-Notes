//
// Created by zyh on 2026/8/17.
//

#include <stdio.h>

// 朴素实现
void insertSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int toInsert = arr[i], j = i;
        while (j > 0 && arr[j - 1] > toInsert) {  // 只要j>0并且前一个还大于当前待插入元素，就一直往前找
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = toInsert;
    }
}

// 进阶实现--二分搜索
int binarySearch(int arr[], int left, int right, int target) {
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (target == arr[mid])
            return mid;

        if (target < arr[mid])
            right = mid -1;
        else
            left = mid + 1;
    }
    return left;
}

void insertSort_advanced(int arr[], int size){
    for (int i = 1; i < size; ++i) {
        int temp = arr[i];
        int j = binarySearch(arr, 0, i - 1, temp);   //由二分搜索来确定插入位置
        for (int k = i; k > j; k--)
            arr[k] = arr[k - 1];   //依然是将后面的元素后移
        arr[j] = temp;
    }
}


int main() {
    int arr[] = {3, 5, 7, 2, 9, 0, 6, 1, 8, 4};
    insertSort_advanced(arr, sizeof(arr) / sizeof(int));

    for (int i = 0; i < 10; ++i)
        printf("%d ", arr[i]);
}