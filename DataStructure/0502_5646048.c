#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

typedef int element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	return -1;
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_queuefull(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_queueempty(QueueType* q) {
	return (q->front == q->rear);
}

void enqueue(QueueType* q, element item) {
	if (is_queuefull(q)) {
		error("Queue is full.");
	}
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = item;
	}
}

element dequeue(QueueType* q) {
	if (is_queueempty(q)) {
		error("Queue is empty");
	}
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->data[q->front];
	}
}

void print_queue(QueueType* q) {
	int i;
	if (is_queueempty(q)) {
		error("Queue is empty");
	}
	else {
		for (i = (q->front + 1) % MAX_QUEUE_SIZE; i != q->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
			printf("[%2d] %2d, ", i, q->data[i]);
		}
		printf("[%2d] %2d\n", i, q->data[i]);
	}
}

void init_stack(StackType* s) {
	s->top = -1;
}

int is_stackfull(StackType* s) {
	return(s->top == (MAX_STACK_SIZE - 1));
}

int is_stackempty(StackType* s) {
	return(s->top == -1);
}

void push(StackType* s, element item) {
	if (is_stackfull(s)) {
		error("Stack is full");
	}
	else {
		s->top = s->top + 1;
		s->data[s->top] = item;
	}
}

element pop(StackType* s) {
	element r;
	if (is_stackempty(s)) {
		error("Stack is empty");
	}
	else {
		r = s->data[s->top];
		s->top = s->top - 1;
	}
	return r;
}

void print_stack(StackType* s) {
	if (is_stackempty(s)) {
		error("Stack is empty");
	}
	printf("Stack element: ");
	for (int i = 0; i <= s->top; i++) {
		printf("%d ", s->data[i]);
	}
	printf("\n");
}

int main(void){
	int choice;
	char str[MAX_QUEUE_SIZE];

	QueueType q;
	StackType s;

	init_queue(&q);
	init_stack(&s);

	while (1) {
		printf("1. 회문 입력\n");
		printf("2. 회문 검사\n");
		printf("3. 종료\n");
		printf("메뉴 선택: ");
		scanf_s("%d", &choice);
		while (getchar() != '\n'); // 입력 버퍼 지우기

		switch (choice) {
		case 1:
			printf("회문을 입력하세요: ");
			fgets(str, sizeof(str), stdin);
			break;
		case 2:
			// 회문 검사 구문
			printf("\n입력한 문자열: %s\n", str);
			for (int i = 0; i < strlen(str); i++) {
				if (isalpha(str[i])) {
					enqueue(&q, tolower(str[i]));
					push(&s, tolower(str[i]));
				}
			}

			int is_palindrome = 1;
			while (!is_queueempty(&q) && !is_stackempty(&s)) {
				if (dequeue(&q) != pop(&s)) {
					is_palindrome = 0;
					break;
				}
			}

			if (is_palindrome)
				printf("입력한 문자열은 회문입니다.\n");
			else
				printf("입력한 문자열은 회문이 아닙니다.\n");

			// 초기화
			init_queue(&q);
			init_stack(&s);
			break;
		case 3:
			exit(0);
		default:
			printf("잘못된 메뉴 선택\n");
			break;
		}
	}
	return 0;
}