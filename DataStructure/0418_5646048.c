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

//���� ǥ�� ���� ��� �Լ�
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

// ������ �켱���� ��ȯ
int prec(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

//���� ǥ�� ����->���� ǥ�� ����
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
                postfixExpression[j++] = pop(&s); // ���������� ��ȯ�� �����ڸ� postfixExpression�� ����
            }
            push(&s, (int)exp[i]);
            break;
        case '(':
            push(&s, (int)exp[i]);
            break;
        case ')':
            while (!is_empty(&s) && peek(&s) != '(') {
                postfixExpression[j++] = pop(&s); // ��ȣ �ȿ� �ִ� �����ڸ� postfixExpression�� ����
            }
            pop(&s); // ���� ��ȣ ����
            break;
        default:
            postfixExpression[j++] = exp[i]; // �ǿ����ڸ� postfixExpression�� ����
            break;
        }
    }

    while (!is_empty(&s)) {
        postfixExpression[j++] = pop(&s); // ���ÿ� ���� �����ڸ� postfixExpression�� ����
    }

    postfixExpression[j] = '\0'; // ���ڿ� ���� NULL �߰�
}

int main(void) {
    char infixExpression[MAX_STACK_SIZE];
    char postfixExpression[MAX_STACK_SIZE];

    while (1) {
        printf("������ ���� �޴��� �����ϴ� ���α׷� �Դϴ�: \n");
        printf("1. �������� �Է� ���� \n");
        printf("2. �������� ���������� ��ȯ \n");
        printf("3. �������� ��� \n");
        printf("4. ���� \n");
        printf("�޴��� �����ϼ���: ");

        int choice;
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("�������� �Է��ϼ���: ");
            getchar();
            fgets(infixExpression, sizeof(infixExpression), stdin);
            printf("�Էµ� ������: %s\n", infixExpression);
            break;
        case 2:
            printf("�������� ���������� ��ȯ�� ���: ");
            infix_to_postfix(infixExpression, postfixExpression); // postfixExpression �迭�� ����
            printf("%s\n", postfixExpression); // ����� ���
            break;
        case 3:
            printf("�������� ���������� ��ȯ�� ���: ");
            infix_to_postfix(infixExpression, postfixExpression);
            printf("\n");
            printf("�������� ����� ���: %d\n", eval(postfixExpression));
            break;
        case 4:
            printf("���α׷��� �����մϴ�. \n");
            exit(0);
            break;
        default:
            printf("�߸��� �޴� �����Դϴ�. �ٽ� �����ϼ���. \n");
            break;
        }
    }
    

    return 0;
}