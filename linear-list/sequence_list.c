//
// Created by zyh on 2026/7/13.
//

#include <stdio.h>
#include <stdlib.h>
// 顺序表

typedef int T;

struct List {
    T *array; //指向顺序表的底层数组
    int capacity; //数组的容量
    int size;
};

typedef struct List *ArrayList; //因为是数组实现，所以就叫ArrayList，这里直接将List的指针起别名

_Bool initList(ArrayList list) {
    //这里就默认所有的顺序表初始大小都为10吧，随意
    list->array = malloc(sizeof(T) * 10); //使用malloc函数申请10个int大小的内存空间，作为底层数组使用
    if (list->array == NULL)
        return 0; //需要判断如果申请的结果为NULL的话表示内存空间申请失败

    list->capacity = 10; //容量设定为10
    list->size = 0;
    return 1;
}

// 插入元素
_Bool insertElement(ArrayList list, T element, int index) {
    // index是按位序计算的，从1开始，一般都是第index个元素

    // 合法检查
    if (index < 1 || index > list->size + 1)
        return 0;

    // 扩容
    if (list->size >= list->capacity) {
        int new_capacity = list->capacity * 2;
        T* new_array = realloc(list->array, sizeof(T) * new_capacity);
        if (new_array == NULL)
            return 0;

        list->array = new_array;
        list->capacity = new_capacity;
    }

    // 插入
    for (int i = list->size; i > index - 1; --i)
        list->array[i] = list->array[i - 1];
    list->array[index - 1] = element;
    list->size++;

    return 1;
}

// 删除元素
_Bool deleteElement(ArrayList list, int index) {
    // index是按位序计算的，从1开始，一般都是第index个元素
    if (index < 1 || index > list->size)
        return 0;

    for (int i = index - 1; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];
    list->size--;

    return 1;
}

// 获取size
int sizeList(ArrayList list){
    return list->size;   //直接返回size就完事
}

// 按位置获取元素
T * getElement(ArrayList list, int index){
    // index是按位序计算的，从1开始，一般都是第index个元素
    if(index < 1 || index > list->size)
        return NULL;   //如果超出范围就返回NULL
    return &list->array[index - 1];
}

// 查找指定元素的位置
int findElement(ArrayList list, T element){
    for (int i = 0; i < list->size; ++i) {   //一直遍历，如果找到那就返回位序
        if (list->array[i] == element)
            return i + 1;  // 返回位序
    }
    return -1;  //如果遍历完了都没找到，那么就返回-1
}

void printList(ArrayList list){   //编写一个函数用于打印表当前的数据
    for (int i = 0; i < list->size; ++i)   //表里面每个元素都拿出来打印一次
        printf("%d ", list->array[i]);
    printf("\n");
}

int main() {
    struct List list;
    if (initList(&list)) {
        for (int i = 0; i < 30; ++i)
            insertElement(&list, i, i);
        printList(&list);
        printf("%d", list.capacity);
    }
    else {
        printf("顺序表初始化失败，无法启动程序！");
    }
}
