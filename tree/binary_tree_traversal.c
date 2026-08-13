//
// Created by zyh on 2026/7/22.
//

#include <stdio.h>
#include <stdlib.h>
// 二叉树-遍历

/*
        A
       / \
      B   C
     / \   \
    D   E   F
*/

typedef char E;

struct TreeNode {
    E element;    //存放元素
    struct TreeNode* left;   //指向左子树的指针
    struct TreeNode* right;   //指向右子树的指针
};

typedef struct TreeNode* Node;

void preOrder(Node target) {  // 前序遍历-递归
    if (target == NULL)
        return;

    printf("%c", target->element);
    preOrder(target->left);
    preOrder(target->right);
}

void inOrder(Node target) {  // 中序遍历-递归
    if (target == NULL)
        return;

    inOrder(target->left);
    printf("%c", target->element);
    inOrder(target->right);
}

void postOrder(Node target) {  // 后序遍历-递归
    if (target == NULL)
        return;

    postOrder(target->left);
    postOrder(target->right);
    printf("%c", target->element);
}

//--------------- 队列 ----------------
typedef Node T;   //还是将Node作为元素

struct QueueNode {
    T element;
    struct QueueNode * next;
};

typedef struct QueueNode * QNode;

struct Queue{
    QNode front, rear;
};

typedef struct Queue * LinkedQueue;

_Bool initQueue(LinkedQueue queue) {
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL)
        return 0;
    queue->front = queue->rear = node;
    return 1;
}

_Bool enqueue(LinkedQueue queue, T element) {
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL)
        return 0;
    node->element = element;
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    return 1;
}


T dequeue(LinkedQueue queue){
    QNode node = queue->front->next;
    T e = node->element;
    queue->front->next = node->next;
    if(queue->rear == node)
        queue->rear = queue->front;

    free(node);
    return e;
}

_Bool isEmpty(LinkedQueue queue){
    return queue->front == queue->rear;
}

//--------------------------------


void levelOrder(Node root) {  // 层序遍历
    struct Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);

    while (!isEmpty(&queue)) {
        Node node = dequeue(&queue);
        printf("%c", node->element);

        if (node->left)
            enqueue(&queue, node->left);
        if (node->right)
            enqueue(&queue, node->right);
    }
}

int main(){
    Node a = malloc(sizeof(struct TreeNode));
    Node b = malloc(sizeof(struct TreeNode));
    Node c = malloc(sizeof(struct TreeNode));
    Node d = malloc(sizeof(struct TreeNode));
    Node e = malloc(sizeof(struct TreeNode));
    Node f = malloc(sizeof(struct TreeNode));
    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';
    f->element = 'F';

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right = f;
    c->left = NULL;
    d->left = d->right = NULL;
    e->left = e->right = NULL;
    f->left = f->right = NULL;

    preOrder(a);    // ABDECF
    printf("\n");
    inOrder(a);     // DBEACF
    printf("\n");
    postOrder(a);   // DEBFCA
    printf("\n");
    levelOrder(a);  // ABCDEF

    free(a), free(b), free(c),
    free(d), free(e), free(f);

    return 0;
}

/*
// 自己写栈实现
typedef char E;

struct TreeNode {
    E element;
    struct TreeNode * left;
    struct TreeNode * right;
    int flag;   //需要经历左右子树都被遍历才行，这里用flag存一下状态，0表示左子树遍历完成，1表示右子树遍历完成
};

typedef struct TreeNode * Node;

//------------- 栈 -------------------
typedef Node T;   //这里栈内元素类型定义为上面的Node，也就是二叉树结点指针

struct StackNode {
    T element;
    struct StackNode * next;
};

typedef struct StackNode * SNode;  //这里就命名为SNode，不然跟上面冲突了就不好了

void initStack(SNode head){
    head->next = NULL;
}

_Bool pushStack(SNode head, T element){
    SNode node = malloc(sizeof(struct StackNode));
    if(node == NULL) return 0;
    node->next = head->next;
    node->element = element;
    head->next = node;
    return 1;
}

_Bool isEmpty(SNode head){
    return head->next == NULL;
}

T popStack(SNode head){
    SNode top = head->next;
    head->next = head->next->next;
    T e = top->element;
    free(top);
    return e;
}

T peekStack(SNode head){   //这里新增一个peek操作，用于获取栈顶元素的值，但是不出栈，仅仅是值获取
    return head->next->element;
}

//---------------  前序 ----------------------

void preOrder(Node root){
    struct StackNode stack;  //栈先搞出来
    initStack(&stack);
    while (root || !isEmpty(&stack)){   //两个条件，只有当栈空并且节点为NULL时才终止循环
        while (root) {    //按照我们的思路，先不断遍历左子树，直到没有为止
            pushStack(&stack, root);   //途中每经过一个结点，就将结点丢进栈中
            printf("%c", root->element);   //然后打印当前结点元素值
            root = root->left;  //继续遍历下一个左孩子结点
        }
        Node node = popStack(&stack);  //经过前面的循环，明确左子树全部走完了，接着就是右子树了
        root = node->right;  //得到右孩子，如果有右孩子，下一轮会重复上面的步骤；如果没有右孩子那么这里的root就被赋值为NULL了，下一轮开始会直接跳过上面的while，继续出栈下一个结点再找右子树
    }
}

//---------------  中序 ----------------------

void inOrder(Node root){
    struct StackNode stack;  //栈先搞出来
    initStack(&stack);
    while (root || !isEmpty(&stack)){   //两个条件，只有当栈空并且节点为NULL时才终止循环
        while (root) {    //按照我们的思路，先不断遍历左子树，直到没有为止
            pushStack(&stack, root);   //途中每经过一个结点，就将结点丢进栈中
            root = root->left;  //继续遍历下一个左孩子结点
        }
        Node node = popStack(&stack);  //经过前面的循环，明确左子树全部走完了，接着就是右子树了
        printf("%c", root->element);   //然后打印当前结点元素值
        root = node->right;  //得到右孩子，如果有右孩子，下一轮会重复上面的步骤；如果没有右孩子那么这里的root就被赋值为NULL了，下一轮开始会直接跳过上面的while，继续出栈下一个结点再找右子树
    }
}

//---------------  后序 ----------------------

void postOrder(Node root){
    struct StackNode stack;
    initStack(&stack);
    while (root || !isEmpty(&stack)){   //其他都不变
        while (root) {
            pushStack(&stack, root);
            root->flag = 0;    //首次入栈时，只能代表左子树遍历完成，所以flag置0
            root = root->left;
        }
        root = peekStack(&stack);   //注意这里只是获取到结点，并没有进行出栈操作，因为需要等待右子树遍历完才能出栈
        if(root->flag == 0) {    //如果仅仅遍历了左子树，那么flag就等于0
            root->flag = 1;   //此时标记为1表示遍历右子树
            root = root->right;   //这里跟之前是一样的
        } else {
            printf("%c", root->element);   //当flag为1时走这边，此时左右都遍历完成了，这时再打印值出来
            popStack(&stack);   //这时再把对应的结点出栈，因为左右都完事了
            root = NULL;   //置为NULL，下一轮直接跳过while，然后继续取栈中剩余的结点，重复上述操作
        }
    }
}
 */