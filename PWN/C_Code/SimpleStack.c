#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 栈结构定义
typedef struct myStack {
    int* data;
    int size;
    int top;

    // 成员函数（函数指针）
    bool (*push)(struct myStack*, int);
    int  (*pop)(struct myStack*);
    bool (*is_empty)(struct myStack*);
    bool (*is_full)(struct myStack*);
    void (*destroy)(struct myStack*);
} Stack;

// 函数实现
bool push(Stack* s, int value) {
    if (s->top >= s->size - 1) {
        printf("栈满，无法插入！\n");
        return false;
    }
    s->data[++(s->top)] = value;
    printf("插入元素：%d\n", value);
    return true;
}

int pop(Stack* s) {
    if (s->top < 0) {
        printf("栈空，无法弹出！\n");
        return -9999;  // 特殊值，避免与实际数据冲突
    }
    return s->data[(s->top)--];     // 先返回栈顶元素，再将栈顶指针下移
}

bool is_empty(Stack* s) {
    return s->top < 0;
}

bool is_full(Stack* s) {
    return s->top >= s->size - 1;
}

// 销毁栈
void destroy(Stack* s) {
    free(s->data);
    s->data = NULL;
    s->size = 0;
    s->top = -1;
}

// 初始化函数
void init_stack(Stack* s, int capacity) {
    s->size = capacity;
    s->data = (int*)malloc(sizeof(int) * capacity);
    s->top = -1;

    // 绑定成员函数
    s->push = push;
    s->pop = pop;
    s->is_empty = is_empty;
    s->is_full = is_full;
    s->destroy = destroy;
}

// 测试主程序
int main() {
    Stack s;
    int n;
    printf("Stack的大小:%d\n",sizeof(Stack));
    printf("请输入栈的容量：");
    scanf("%d", &n);

    init_stack(&s, n);

    s.push(&s, 10);
    s.push(&s, 20);
    s.push(&s, 30);

    printf("弹出元素：%d\n", s.pop(&s));
    printf("弹出元素：%d\n", s.pop(&s));

    if (s.is_empty(&s)) {
        printf("栈已空。\n");
    } else {
        printf("栈中还有元素。\n");
    }

    s.destroy(&s);

    return 0;
}
