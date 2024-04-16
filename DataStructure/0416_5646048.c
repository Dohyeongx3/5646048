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
                    fprintf(stderr, "0으로 나누기 오류\n");
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

// 후위 표기식 확인 함수
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

    // 연산자는 피연산자보다 하나 작아야 합니다.
    if (operand_count - operator_count != 1) {
        fprintf(stderr, "잘못된 후위 표기식입니다. 연산자와 피연산자의 수가 일치하지 않습니다.\n");
        return false;
    }

    // 스택이 비어있지 않아야 합니다.
    if (operand_count == 0 || operator_count == 0) {
        fprintf(stderr, "잘못된 후위 표기식입니다. 피연산자나 연산자가 없습니다.\n");
        return false;
    }

    return true;
}

int main(void) {
    char expression[MAX_STACK_SIZE];
    int result;

    printf("후위 표기식을 입력하시오: ");
    fgets(expression, sizeof(expression), stdin);
    if (!is_postfix(expression)) {
        // 후위 표기식이 아닌 경우 에러 메시지 출력 후 프로그램 종료
        fprintf(stderr, "입력한 식은 후위 표기식이 아닙니다.\n");
        return 1;
    }
    result = eval(expression);
    printf("결과: %d\n", result);
    return 0;
}