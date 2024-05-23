#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct {
	int coef;
	int expo;
}element;

typedef struct listNode {
	element data;
	struct listNode* link;
}ListNode;

typedef struct {
	ListNode* head;
	ListNode* tail;
	int size;
}ListType;

ListType* create() {
	ListType* plist = (ListNode*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_first(ListType* plist, element term) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	temp->data = term;
	temp->link = plist->head;
	plist->head = temp;
	if (plist->tail == NULL) {
		plist->tail = temp;
	}
	plist->size++;
}

void insert(ListType* plist, int pos, element term) {
	if (pos == 0) {
		insert_first(plist, term);
	}
	else {
		ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
		ListNode* prev = plist->head;
		for (int i = 1; i < pos; i++) {
			prev = prev->link;
		}
		temp->data = term;
		temp->link = prev->link;
		prev->link = temp;
		if (temp->link == NULL) {
			plist->tail = temp;
		}
		plist->size++;
	}
}

void delete(ListType* plist, int pos) {
	if (pos == 0) {
		ListNode* temp = plist->head;
		plist->head = plist->head->link;
		free(temp);
		if (plist->head == NULL) {
			plist->tail = NULL;
		}
	}
	else {
		ListNode* prev = plist->head;
		for (int i = 1; i < pos; i++) {
			prev = prev->link;
		}
		ListNode* temp = prev->link;
		prev->link = temp->link;
		if (temp->link == NULL) {
			plist->tail = prev;
		}
		free(temp);
	}
	plist->size--;
}

ListNode* search(ListType* plist, int expo) {
	ListNode* temp = plist->head;
	while (temp != NULL) {
		if (temp->data.expo == expo) {
			return temp;
		}
		temp = temp->link;
	}
	return NULL;
}

void insert_last(ListType* plist, element term) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	temp->data = term;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) {
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;

	while ((a != NULL) && (b != NULL)) {
		if (a->data.expo == b->data.expo) {
			int sum;
			sum = a->data.coef + b->data.coef;
			if (sum != 0) {
				element x;
				x.coef = sum, x.expo = a->data.expo;
				insert_last(plist3, x);
				a = a->link, b = b->link;
			}
		}
		else if (a->data.expo > b->data.expo) {
			insert_last(plist3, a->data);
			a = a->link;
		}
		else {
			insert_last(plist3, b->data);
			b = b->link;
		}
	}

	while (a != NULL) {
		insert_last(plist3, a->data);
		a = a->link;
	}
	while (b != NULL) {
		insert_last(plist3, b->data);
		b = b->link;
	}
}

void print_poly(ListType* plist) {
	ListNode* np = plist->head;

	while (np != NULL) {
		printf("%2dx^%2d", np->data.coef, np->data.expo);
		if (np->link != NULL) {
			printf(" + ");
		}
		np = np->link;
	}
	printf("\n");
}

void parse_poly(char* input, ListType* plist) {
	char* context = NULL;
	char* token = strtok_s(input, "+", &context);
	while (token != NULL) {
		element term;
		if (sscanf_s(token, "%dx^%d", &term.coef, &term.expo) != 2) {
			printf("잘못된 입력입니다: %s\n", token);
			return;
		}
		insert_last(plist, term);
		token = strtok_s(NULL, "+", &context);
	}
}

int main(void) {
	ListType* list1, * list2, * list3;
	list1 = create();
	list2 = create();
	list3 = create();

	char input1[100];
	char input2[100];

	printf("첫 번째 다항식을 입력하세요: ");
	fgets(input1, 100, stdin);
	input1[strcspn(input1, "\n")] = 0; // 개행 문자 제거

	printf("두 번째 다항식을 입력하세요: ");
	fgets(input2, 100, stdin);
	input2[strcspn(input2, "\n")] = 0; // 개행 문자 제거

	parse_poly(input1, list1);
	parse_poly(input2, list2);

	printf("첫 번째 다항식: ");
	print_poly(list1);

	printf("두 번째 다항식: ");
	print_poly(list2);

	poly_add(list1, list2, list3);
	printf("합 다항식: ");
	print_poly(list3);

	free(list1);
	free(list2);
	free(list3);
	return 0;
}