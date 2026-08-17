//
// Created by zyh on 2026/8/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        bool haveSwitch = false;
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                haveSwitch = true;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if (!haveSwitch)
            break;
    }
}

int main() {
    int arr[] = {3, 5, 7, 2, 9, 0, 6, 1, 8, 4};
    bubbleSort(arr, sizeof(arr) / sizeof(int));

    for (int i = 0; i < 10; ++i)
        printf("%d ", arr[i]);
}
