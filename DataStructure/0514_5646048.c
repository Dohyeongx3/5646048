#include<stdio.h>
#define MAX_LIST_SIZE 100

typedef int element;

typedef struct {
	element array[MAX_LIST_SIZE];
	int size;
}ArrayListType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	return -1;
}

void init(ArrayListType* L) {
	L->size = 0;
}

int is_full(ArrayListType* L) {
	return (L->size == MAX_LIST_SIZE);
}

int is_empty(ArrayListType* L) {
	return L->size == 0;
}

void insert(ArrayListType* L, int pos, element item) {
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = L->size - 1; i >= pos; i = i - 1)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size = L->size + 1;
	}
}

void insert_last(ArrayListType* L, element item) {
	if (is_full(L))
		error("����Ʈ �����÷ο�");
	L->array[L->size++] = item;
}

element delete(ArrayListType* L, int pos) {
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	else {
		element item = L->array[pos];
		for (int i = pos; i < (L->size - 1); i++)
			L->array[i] = L->array[i + 1];
		L->size = L->size - 1;
		return item;
	}
}

void insert_first(ArrayListType* L, element item) {
	insert(L, 0, item);
}

void clear(ArrayListType* L) {
	init(L);
}

element get_entry(ArrayListType* L, int pos) {
	if (pos > 0 || pos < L->size)
		return L->array[pos];
	else {
		error("��ġ ����");
		return -1;
	}
}

int get_length(ArrayListType* L) {
	return L->size;
}

void print_list(ArrayListType* L) {
	for (int i = 0; i < L->size; i++)
		printf("%2d->", L->array[i]);
	printf("NULL\n");
}


int main(void) {
    ArrayListType list;

    init(&list);

    int choice;

    while (1) {
        printf("\n�޴�: \n");
        printf("1. ����Ʈ�� �߰� \n");
        printf("2. ����Ʈ���� ���� \n");
        printf("3. ����Ʈ ��� \n");
        printf("0. ���α׷� ���� \n");
        printf("����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            if (is_full(&list)) {
                printf("����Ʈ�� �� á���ϴ�. \n");
            }
            else {
                int pos, item;
                printf("���ڸ� �Է��ϼ���: ");
                scanf_s("%d", &item);
                printf("�߰��� ��ġ�� �Է��ϼ���: ");
                scanf_s("%d", &pos);
                insert(&list, pos, item);
                printf("���� �Ϸ�.\n");
                printf("�������� �̵� Ƚ��: %d\n", list.size - 1 - pos);
            }
            break;
        case 2:
            if (is_empty(&list)) {
                printf("����Ʈ�� ����ֽ��ϴ�. \n");
            }
            else {
                int pos;
                printf("������ ��ġ�� �Է��ϼ���: ");
                scanf_s("%d", &pos);
                element deleted_item = delete(&list, pos);
                printf("%d �����Ϸ�.\n", deleted_item);
                printf("�������� �̵� Ƚ��: %d\n", list.size - pos);
            }
            break;
        case 3:
            print_list(&list);
            break;
        case 0:
            printf("���α׷� ����\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ��� \n");
        }
    }
}