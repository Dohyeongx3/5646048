#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_STACK_SIZE 5

typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

//create : 이미 만들었음
//delete : 할수없음

//is_full
int is_full() {
    return (top == MAX_STACK_SIZE - 1);
}

//is_empty
int is_empty() {
    return (top == -1);
}

// push
void push(element item) {
    if (is_full()) {
        fprintf(stderr, "Stack Overflow\n");
        return;
    }
    else {
        top = top + 1;
        stack[top] = item;
    }
    printf("even push : %d \n", item);
}

// pop
element pop() {
    element r;
    if (is_empty()) {
        fprintf(stderr, "stack Underflow \n");
        return -1;
    }
    else {
        r = stack[top];
        top = top - 1;
    }
    printf("odd pop : %d\n", r);
    return r;
}

element peek() {
    element r;
    if (is_empty()) {
        fprintf(stderr, "stack is empty \n");
        return -1;
    }
    else {
        return (stack[top]);
    }
}

// 현재 스택 요소 출력 함수
void print_stack() {
    if (is_empty()) {
        printf("Stack is empty\n");
        return;
    }
    else {
        printf("stack elements: ");
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}


int main(void) {
    element e;
    srand((unsigned int)(time(NULL)));

    for (int i = 0; i < 30; i++) {
        e = (rand() % 100) + 1;
        if (e % 2 == 0) {
            printf("current rand_num : %d \n", e);
            push(e);
        }
        else {
            printf("current rand_num : %d\n", e);
            e = pop();
        }
        print_stack();
    }
    return 0;
}