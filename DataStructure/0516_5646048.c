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

ListNode* insert(ListNode* head, ListNode* pre, element value) {   //main 함수 head 와 다른포인터
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
        printf("\n메뉴: \n");
        printf("1. 숫자를 위치에 삽입 \n");
        printf("2. 위치에서 숫자를 삭제 \n");
        printf("3. 리스트 출력 \n");
        printf("0. 프로그램 종료 \n");
        printf("선택하세요: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("삽입할 숫자를 입력하세요: ");
            scanf_s("%d", &value);
            printf("삽입할 위치를 입력하세요: ");
            scanf_s("%d", &position);
            if (position == 0) {
                head = insert_first(head, value);
                printf("삽입시 링크를 따라 이동한 횟수: 1\n");
            }
            else {
                ListNode* p = head;
                
                for (i = 0; i < position - 1 && p != NULL; i++) {
                    p = p->link;
                }
                if (p != NULL) {
                    head = insert(head, p, value);
                    printf("삽입시 링크를 따라 이동한 횟수: %d\n", i + 1);
                }
                else {
                    printf("유효하지 않은 위치입니다.\n");
                }
            }
            break;
        case 2:
            printf("삭제할 위치를 입력하세요: ");
            scanf_s("%d", &position);
            if (position == 0) {
                head = delete_first(head);
                printf("삭제시 링크를 따라 이동한 횟수 : 1\n");
            }
            else {
                ListNode* p = head;
                for (i = 0; i < position - 1 && p != NULL && p->link != NULL; i++) {
                    p = p->link;
                }
                if (p != NULL && p->link != NULL) {
                    head = delete(head, p);
                    printf("삭제시 링크를 따라 이동한 횟수 : %d\n", i + 1);
                }
                else {
                    printf("유효하지 않은 위치입니다.\n");
                }
            }
            break;
        case 3:
            print_list(head);
            break;
        case 0:
            exit(0);
        default:
            printf("유효하지 않은 선택입니다. \n");
        }
    }
    return 0;
}