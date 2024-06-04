#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct DlistNode {
	element data;
	struct DlistNode* llink, * rlink;
}DListNode;

void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode)); //1
	newnode->data = data;
	newnode->llink = before; //2
	newnode->rlink = before->rlink; //3
	before->rlink = newnode; //4
	newnode->rlink->llink = newnode; //5
}

element ddelete(DListNode* head, DListNode* removed) {
	element r;
	if (removed == head)
		return;
	r = removed->data;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
	return r;
}

void print_dlist(DListNode* head) {
	DListNode* p;
	for (p = head->rlink; p != head; p = p->rlink) {
		printf("<-%2d->", p->data);
	}
	printf("\n");
}

int main(void) {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	
	int choice, data;
	element deleted;
	
	while (1) {
		printf("\n�޴� \n");
		printf("1. ���� �Է� �޾Ƽ� ����Ʈ ó���� �߰�\n");
		printf("2. ���� �Է� �޾Ƽ� ����Ʈ �������� �߰�\n");
		printf("3. ����Ʈ ó�� ��� ���� \n");
		printf("4. ����Ʈ ������ ��� ���� \n");
		printf("5. ����Ʈ ����Ʈ \n");
		printf("6. ���� \n");
		printf("����: ");
		scanf_s("%d", &choice);

		switch (choice) {
		case 1:
			printf("�߰��� ���ڸ� �Է��ϼ���: ");
			scanf_s("%d", &data);
			dinsert(head, data);
			break;
		case 2:
			printf("�߰��� ���ڸ� �Է��ϼ���: ");
			scanf_s("%d", &data);
			dinsert(head->llink, data);
			break;
		case 3:
			if (head->rlink == head) {
				printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
			}
			else {
				deleted = ddelete(head, head->rlink);
				printf("������ ������: %d\n", deleted);
			}
			break;
		case 4:
			if (head->rlink == head) {
				printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
			}
			else {
				deleted = ddelete(head, head->llink);
				printf("������ ������: %d\n", deleted);
			}
			break;
		case 5:
			print_dlist(head);
			break;
		case 6:
			printf("���α׷� ���� \n");
			exit(0);
		default:
			printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ��� \n");
		}
	}

	return 0;
}