//
// Created by zyh on 2026/7/13.
//

#include <stdio.h>
// 二分搜索算法

int binarySearch(int* nums, int target, int left, int right) {  // 递归写法
    if (left > right)
        return -1;

    int mid = (left + right) / 2;
    if (nums[mid] == target)
        return mid;
    if (nums[mid] > target) {  // target在左
        right = mid - 1;
        return binarySearch(nums, target, left, right);
    }
    else {
        left = mid + 1;
        return binarySearch(nums, target, left, right);
    }
}

int search(int* nums, int numSize, int target) {
    return binarySearch(nums, target, 0, numSize - 1);
}
