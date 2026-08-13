//
// Created by zyh on 2026/7/16.
//

#include <stdio.h>
#include <stdlib.h>
// 栈FILO

typedef int T;

struct Stack {
    T* array;
    int capacity;
    int top;  // 这里使用top来表示当前的栈顶位置，存的是栈顶元素的下标
};

typedef struct Stack* ArrayStack;

_Bool initStack(ArrayStack stack) {
    stack->array = malloc(sizeof(T) * 10);
    if (!stack->array)
        return 0;

    stack->capacity = 10;
    stack->top = -1;

    return 1;
}

_Bool push(ArrayStack stack, T element) {
    if (stack->top + 1 >= stack->capacity) {
        int newCap = stack->capacity * 2;
        T* new_array = realloc(stack->array,sizeof(T) * newCap);
        if (!new_array)
            return 0;

        stack->array = new_array;
        stack->capacity = newCap;
    }

    stack->top++;
    stack->array[stack->top] = element;
    return 1;
}

_Bool isEmpty(ArrayStack stack) {
    return stack->top == -1;
}

T pop(ArrayStack stack) {
    return stack->array[stack->top--];
}

void printStack(ArrayStack stack){
    printf("| ");
    for (int i = 0; i < stack->top + 1; ++i) {
        printf("%d, ", stack->array[i]);
    }
    printf("\n");
}

int main(){
    struct Stack stack;
    initStack(&stack);
    for (int i = 0; i < 3; ++i) {
        push(&stack, i*100);
    }
    printStack(&stack);
    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));   //将栈中所有元素依次出栈
    }
}