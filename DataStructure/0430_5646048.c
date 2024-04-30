#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 6

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	return -1;
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		error("Queue is full.");
	}
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = item;
	}
}

element dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("Queue is empty");
	}
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->data[q->front];
	}
}

void print_queue(QueueType* q) {
	int i;
	if (is_empty(q)) {
		error("Queue is empty");
	}
	else {
		for (i = (q->front + 1) % MAX_QUEUE_SIZE; i != q->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
			printf("[%2d] %2d, ", i, q->data[i]);
		}
		printf("[%2d] %2d\n", i, q->data[i]);
	}
}

int main(void) {
	QueueType q;
	element e;
	init_queue(&q);

	int choice;

	while (1) {
		printf("\n1. 큐에 원소를 삽입\n");
		printf("2. 큐에서 원소를 제거\n");
		printf("3. 큐의 원소 출력\n");
		printf("4. 프로그램 종료\n");
		printf("메뉴를 선택하세요: ");
		scanf_s("%d", &choice);

		switch (choice) {
		case 1:
			printf("삽입할 숫자를 입력하세요: ");
			scanf_s("%d", &e);
			enqueue(&q, e);
			break;
		case 2:
			if (!is_empty(&q)) {
				e = dequeue(&q);
				printf("제거된 원소: %d\n", e);
			}
			else {
				printf("큐가 비어있습니다.\n");
			}
			break;
		case 3:
			print_queue(&q);
			break;
		case 4:
			exit(0);
		default:
			printf("잘못된 선택입니다.\n");
		}
	}

	return 0;
}