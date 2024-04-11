#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 5

typedef int element;

typedef struct {
    element* data; // �������� �Ҵ�� �迭
    int top;
    int capacity; // ���� �Ҵ�� �뷮
} StackType;

// ���� ����
StackType* create_stack(int capacity) {
    StackType* s = (StackType*)malloc(sizeof(StackType));
    s->data = (element*)malloc(sizeof(element)*capacity);
    s->top = -1;
    s->capacity = capacity;
    return s;
}

// ���� ���� (�޸� ����)
void delete_stack(StackType* sptr) {
    free(sptr->data);
    free(sptr);
}

// ������ �� á���� Ȯ��
int is_full(StackType* sptr) {
    return (sptr->top == sptr->capacity - 1);
}

// ������ ������� Ȯ��
int is_empty(StackType* sptr) {
    return (sptr->top == -1);
}

// ��Ҹ� ���ÿ� �߰�
void push(StackType* sptr, element item) {
    if (is_full(sptr)) {
        // ������ ���� á�� ��, �뷮�� �� ��� �ø�
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

// ���ÿ��� ��Ҹ� �����ϰ� ��ȯ
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

// ������ ���� ���� �ִ� ��Ҹ� ��ȯ (�������� ����)
element peek(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    else {
        return sptr->data[sptr->top];
    }
}

// ���� ������ ��� ��Ҹ� ���
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

    // ���� ���� (�ʱ� �뷮: 5)
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

    // ���� ���� (�޸� ����)
    delete_stack(s);

    return 0;
}