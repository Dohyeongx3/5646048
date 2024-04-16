#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100

typedef char element;

typedef struct {
    element* data;
    int capacity;
    int top;
} StackType;


void init(StackType* sptr) {
    sptr->data = (element*)malloc(MAX_STACK_SIZE * sizeof(element));
    sptr->top = -1;
    sptr->capacity = MAX_STACK_SIZE;
}

int is_full(StackType* sptr) {
    return (sptr->top == sptr->capacity - 1);
}

int is_empty(StackType* sptr) {
    return (sptr->top == -1);
}

void push(StackType* sptr, element item) {
    if (is_full(sptr)) {
        sptr->capacity *= 2;
        sptr->data = (element*)realloc(sptr->data, sptr->capacity * sizeof(element));
    }
    else {
        sptr->top = sptr->top + 1;
        sptr->data[sptr->top] = item;
    }
}

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
    return r;
}

element peek(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    return sptr->data[sptr->top];
}

void print_stack(StackType* sptr) {
    if (is_empty(sptr)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack element: ");
    for (int i = 0; i <= sptr->top; i++) {
        printf("%d ", sptr->data[i]);
    }
    printf("\n");
}

int eval(char* expression) {
    StackType s;
    char ch;

    init(&s);
    for (int i = 0; expression[i] != '\0'; i++) {
        ch = expression[i];
        int value;
        int op1, op2;

        printf("Step[%d]: %c \n", i+1, ch);
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            op1 = pop(&s);
            op2 = pop(&s);
            switch (ch) {
            case '+':
                push(&s, op2 + op1);
                break;
            case '-':
                push(&s, op2 - op1);
                break;
            case '*':
                push(&s, op2 * op1);
                break;
            case '/':
                if (op1 != 0)
                    push(&s, op2 / op1);
                else {
                    fprintf(stderr, "0���� ������ ����\n");
                    return;
                }
                break;
            }
        }
        else if (ch >= '0' && ch <= '9') {
            value = ch - '0';
            push(&s, value);
        }
        print_stack(&s);
    }
    return pop(&s);
}

// ���� ǥ��� Ȯ�� �Լ�
bool is_postfix(char* expression) {
    int operand_count = 0;
    int operator_count = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            operator_count++;
        }
        else if (ch >= '0' && ch <= '9') {
            operand_count++;
        }
    }

    // �����ڴ� �ǿ����ں��� �ϳ� �۾ƾ� �մϴ�.
    if (operand_count - operator_count != 1) {
        fprintf(stderr, "�߸��� ���� ǥ����Դϴ�. �����ڿ� �ǿ������� ���� ��ġ���� �ʽ��ϴ�.\n");
        return false;
    }

    // ������ ������� �ʾƾ� �մϴ�.
    if (operand_count == 0 || operator_count == 0) {
        fprintf(stderr, "�߸��� ���� ǥ����Դϴ�. �ǿ����ڳ� �����ڰ� �����ϴ�.\n");
        return false;
    }

    return true;
}

int main(void) {
    char expression[MAX_STACK_SIZE];
    int result;

    printf("���� ǥ����� �Է��Ͻÿ�: ");
    fgets(expression, sizeof(expression), stdin);
    if (!is_postfix(expression)) {
        // ���� ǥ����� �ƴ� ��� ���� �޽��� ��� �� ���α׷� ����
        fprintf(stderr, "�Է��� ���� ���� ǥ����� �ƴմϴ�.\n");
        return 1;
    }
    result = eval(expression);
    printf("���: %d\n", result);
    return 0;
}