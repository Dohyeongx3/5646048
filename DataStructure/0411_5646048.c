#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 5

typedef int element;

typedef struct {
    element* data; // 동적으로 할당된 배열
    int top;
    int capacity; // 현재 할당된 용량
} StackType;

// 스택 생성
StackType* create_stack(int capacity) {
    StackType* s = (StackType*)malloc(sizeof(StackType));
    s->data = (element*)malloc(sizeof(element)*capacity);
    s->top = -1;
    s->capacity = capacity;
    return s;
}

// 스택 삭제 (메모리 해제)
void delete_stack(StackType* sptr) {
    free(sptr->data);
    free(sptr);
}

// 스택이 꽉 찼는지 확인
int is_full(StackType* sptr) {
    return (sptr->top == sptr->capacity - 1);
}

// 스택이 비었는지 확인
int is_empty(StackType* sptr) {
    return (sptr->top == -1);
}

// 요소를 스택에 추가
void push(StackType* sptr, element item) {
    if (is_full(sptr)) {
        // 스택이 가득 찼을 때, 용량을 두 배로 늘림
        sptr->capacity = sptr->capacity * 2;
        sptr->data = realloc(sptr->data, sptr->capacity * sizeof(element));
        if (sptr->data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            return;
        }
    }

    sptr->top = sptr->top + 1;
    sptr->data[sptr->top] = item;
    printf("even push : %d \n", item);
}

// 스택에서 요소를 제거하고 반환
element pop(StackType* sptr) {
    element r;
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack Underflow\n");
        return -1;
    }
    else {
        r = sptr->data[sptr->top];
        sptr->top = sptr->top - 1;
    }
    printf("odd pop : %d\n", r);
    return r;
}

// 스택의 가장 위에 있는 요소를 반환 (제거하지 않음)
element peek(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    else {
        return sptr->data[sptr->top];
    }
}

// 현재 스택의 모든 요소를 출력
void print_stack(StackType* sptr) {
    if (is_empty(sptr)) {
        printf("Stack is empty\n");
        return;
    }
    else {
        printf("Stack elements: ");
        for (int i = 0; i <= sptr->top; i++) {
            printf("%d ", sptr->data[i]);
        }
        printf("\n");
    }
}

int main(void) {
    element e;
    srand((unsigned int)(time(NULL)));

    // 스택 생성 (초기 용량: 5)
    StackType* s = create_stack(MAX_STACK_SIZE);

    for (int i = 0; i < 30; i++) {
        e = (rand() % 100) + 1;
        if (e % 2 == 0) {
            printf("current rand_num : %d \n", e);
            push(s, e);
        }
        else {
            printf("current rand_num : %d\n", e);
            e = pop(s);
        }
        print_stack(s);
    }

    // 스택 삭제 (메모리 해제)
    delete_stack(s);

    return 0;
}