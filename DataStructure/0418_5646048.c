#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

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

//후위 표기 수식 계산 함수
int eval(char* expression) {
    StackType s;
    char ch;

    init(&s);
    for (int i = 0; expression[i] != '\0'; i++) {
        ch = expression[i];
        int value;
        int op1, op2;

        printf("Step[%d]: %c \n", i + 1, ch);
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

// 연산자 우선순위 반환
int prec(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

//중위 표기 수식->후위 표기 수식
void infix_to_postfix(char exp[], char postfixExpression[]) {
    StackType s;

    init(&s);

    int len = strlen(exp);
    int j = 0;

    for (int i = 0; i < len; i++) {
        switch (exp[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
            while (!is_empty(&s) && (prec(exp[i]) <= prec((char)peek(&s)))) {
                postfixExpression[j++] = pop(&s); // 후위식으로 변환된 연산자를 postfixExpression에 저장
            }
            push(&s, (int)exp[i]);
            break;
        case '(':
            push(&s, (int)exp[i]);
            break;
        case ')':
            while (!is_empty(&s) && peek(&s) != '(') {
                postfixExpression[j++] = pop(&s); // 괄호 안에 있는 연산자를 postfixExpression에 저장
            }
            pop(&s); // 여는 괄호 제거
            break;
        default:
            postfixExpression[j++] = exp[i]; // 피연산자를 postfixExpression에 저장
            break;
        }
    }

    while (!is_empty(&s)) {
        postfixExpression[j++] = pop(&s); // 스택에 남은 연산자를 postfixExpression에 저장
    }

    postfixExpression[j] = '\0'; // 문자열 끝에 NULL 추가
}

int main(void) {
    char infixExpression[MAX_STACK_SIZE];
    char postfixExpression[MAX_STACK_SIZE];

    while (1) {
        printf("다음과 같은 메뉴로 동작하는 프로그램 입니다: \n");
        printf("1. 중위식을 입력 받음 \n");
        printf("2. 중위식을 후위식으로 변환 \n");
        printf("3. 후위식을 계산 \n");
        printf("4. 종료 \n");
        printf("메뉴를 선택하세요: ");

        int choice;
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("중위식을 입력하세요: ");
            getchar();
            fgets(infixExpression, sizeof(infixExpression), stdin);
            printf("입력된 중위식: %s\n", infixExpression);
            break;
        case 2:
            printf("중위식을 후위식으로 변환한 결과: ");
            infix_to_postfix(infixExpression, postfixExpression); // postfixExpression 배열을 전달
            printf("%s\n", postfixExpression); // 결과를 출력
            break;
        case 3:
            printf("중위식을 후위식으로 변환한 결과: ");
            infix_to_postfix(infixExpression, postfixExpression);
            printf("\n");
            printf("후위식을 계산한 결과: %d\n", eval(postfixExpression));
            break;
        case 4:
            printf("프로그램을 종료합니다. \n");
            exit(0);
            break;
        default:
            printf("잘못된 메뉴 선택입니다. 다시 선택하세요. \n");
            break;
        }
    }
    

    return 0;
}