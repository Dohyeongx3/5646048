#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct {
    char name[20];
}element;

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

ListNode* insert_last(ListNode* head, ListNode** tail, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = NULL;
    if (*tail) // *tail�� NULL�� �ƴ� ���, �� ����Ʈ�� ��尡 �ִ� ���
        (*tail)->link = p;
    else      // *tail�� NULL�� ���, �� ����Ʈ�� ����ִ� ���
        head = p;
    *tail = p;  // tail �����͸� ���� �߰��� ���� ����
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
    if (pre == NULL || pre->link == NULL)
        return head;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

ListNode* search_list(ListNode* head, element x) {
    ListNode* p = head;
    while (p != NULL) {
        if (strcmp(p->data.name, x.name) == 0)
            return p;
        p = p->link;
    }
    return NULL;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != (ListNode*)NULL; p = p->link)
        printf("%s->", p->data.name);
    printf("NULL\n");
}

void print_deleted_list(ListNode* deleted_head) {
    for (ListNode* p = deleted_head; p != NULL; p = p->link)
        printf("%s -> ", p->data.name);
    printf("NULL\n");
}

int main(void) {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    ListNode* deleted_head = NULL;
    ListNode* deleted_tail = NULL;

    element fruits[] = { {"Mango"}, {"Orange"}, {"Apple"}, {"Grape"}, {"Cherry"}, {"Plum"}, {"Guava"}, {"Raspberry"}, {"Banana"}, {"Peach"} };
    for (int i = 0; i < 10; i++) {
        head = insert_last(head, &tail, fruits[i]);
    }

    int choice;
    char fruit_name[20];
    element fruit;

    while (1) {
        printf("\n�޴�: \n");
        printf("1. ����Ʈ�� �� �������� ���ο� ���� �߰� \n");
        printf("2. ����Ʈ�� �ִ� ������ ���� \n");
        printf("3. ������ ���� ��� ��� \n");
        printf("4. ���� ���� ��� ��� \n");
        printf("0. ���α׷� ���� \n");
        printf("�����ϼ���: ");
        scanf_s("%d", &choice);
        while (getchar() != '\n'); // �Է� ���� �����

        switch (choice) {
        case 1:
            printf("�߰��� ���� �̸��� �Է��ϼ���: ");
            fgets(fruit_name, sizeof(fruit_name), stdin);
            fruit_name[strcspn(fruit_name, "\n")] = 0; // ���� ���� ����
            strcpy_s(fruit.name, sizeof(fruit.name), fruit_name);
            if (search_list(head, fruit) == NULL) {
                head = insert_last(head, &tail, fruit);
                printf("%s ������ �߰��Ǿ����ϴ�.\n", fruit.name);
            }
            else {
                printf("%s ������ �̹� �����մϴ�.\n", fruit.name);
            }
            break;
        case 2:
            printf("������ ���� �̸��� �Է��ϼ���: ");
            fgets(fruit_name, sizeof(fruit_name), stdin);
            fruit_name[strcspn(fruit_name, "\n")] = 0; // ���� ���� ����
            strcpy_s(fruit.name, sizeof(fruit.name), fruit_name);
            ListNode* current = head;
            ListNode* previous = NULL;
            while (current != NULL && strcmp(current->data.name, fruit.name) != 0) {
                previous = current;
                current = current->link;
            }
            if (current != NULL) {
                if (previous == NULL) {
                    head = delete_first(head);
                }
                else {
                    head = delete(head, previous);
                }
                deleted_head = insert_last(deleted_head, &deleted_tail, fruit);
                printf("%s ������ �����Ǿ����ϴ�.\n", fruit.name);
            }
            else {
                printf("%s ������ �������� �ʽ��ϴ�.\n", fruit.name);
            }
            break;
        case 3:
            printf("������ ���� ���: \n");
            print_deleted_list(deleted_head);
            break;
        case 4:
            print_list(head);
            break;
        case 0:
            exit(0);
        default:
            printf("��ȿ���� ���� �����Դϴ�.\n");
        }
    }
    return 0;
}