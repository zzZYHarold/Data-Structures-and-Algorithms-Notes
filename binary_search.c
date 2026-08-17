//
// Created by zyh on 2026/7/13.
//

#include <stdio.h>
// 二分搜索算法

// 递归写法
int binarySearch_recursion(int* nums, int target, int left, int right) {
    if (left > right)
        return -1;

    int mid = left + (right - left) / 2;  // 防止 left + right 溢出
    if (nums[mid] == target)
        return mid;

    if (nums[mid] > target)   // target在左
        right = mid - 1;
    else
        left = mid + 1;
    return binarySearch_recursion(nums, target, left, right);
}

// 迭代写法
int binarySearch_iteration(int* nums, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (target == nums[mid])
            return mid;

        if (target < nums[mid])
            right = mid -1;
        else
            left = mid + 1;
    }
    return -1;
}

int search(int* nums, int numSize, int target) {
    return binarySearch_recursion(nums, target, 0, numSize - 1);
}
