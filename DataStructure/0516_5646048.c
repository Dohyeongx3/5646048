#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct listNode {
	element data;
	struct listNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {   //main �Լ� head �� �ٸ�������
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link; // <1>
	pre->link = p; //<2>
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL)
		return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != (ListNode*)NULL; p = p->link)
        printf("%2d->", p->data);
    printf("NULL \n");
}

int main(void) {
	ListNode* head = (ListNode*)NULL;

    int choice, position, value,i;

    while (1) {
        printf("\n�޴�: \n");
        printf("1. ���ڸ� ��ġ�� ���� \n");
        printf("2. ��ġ���� ���ڸ� ���� \n");
        printf("3. ����Ʈ ��� \n");
        printf("0. ���α׷� ���� \n");
        printf("�����ϼ���: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("������ ���ڸ� �Է��ϼ���: ");
            scanf_s("%d", &value);
            printf("������ ��ġ�� �Է��ϼ���: ");
            scanf_s("%d", &position);
            if (position == 0) {
                head = insert_first(head, value);
                printf("���Խ� ��ũ�� ���� �̵��� Ƚ��: 1\n");
            }
            else {
                ListNode* p = head;
                
                for (i = 0; i < position - 1 && p != NULL; i++) {
                    p = p->link;
                }
                if (p != NULL) {
                    head = insert(head, p, value);
                    printf("���Խ� ��ũ�� ���� �̵��� Ƚ��: %d\n", i + 1);
                }
                else {
                    printf("��ȿ���� ���� ��ġ�Դϴ�.\n");
                }
            }
            break;
        case 2:
            printf("������ ��ġ�� �Է��ϼ���: ");
            scanf_s("%d", &position);
            if (position == 0) {
                head = delete_first(head);
                printf("������ ��ũ�� ���� �̵��� Ƚ�� : 1\n");
            }
            else {
                ListNode* p = head;
                for (i = 0; i < position - 1 && p != NULL && p->link != NULL; i++) {
                    p = p->link;
                }
                if (p != NULL && p->link != NULL) {
                    head = delete(head, p);
                    printf("������ ��ũ�� ���� �̵��� Ƚ�� : %d\n", i + 1);
                }
                else {
                    printf("��ȿ���� ���� ��ġ�Դϴ�.\n");
                }
            }
            break;
        case 3:
            print_list(head);
            break;
        case 0:
            exit(0);
        default:
            printf("��ȿ���� ���� �����Դϴ�. \n");
        }
    }
    return 0;
}