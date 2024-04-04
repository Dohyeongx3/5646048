#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_TERMS 101

typedef struct term {
    float coef;
    int expon;
} term;

void print_poly(term* terms, int start, int end) {
    for (int i = start; i < end; i++) {
        printf("%3.1fx^%1d + ", terms[i].coef, terms[i].expon);
    }
    printf("%3.1f\n", terms[end].coef);
}

void attach(term* terms, int* avail, float coef, int expon) {
    if (*avail >= MAX_TERMS) {
        fprintf(stderr, "���� ������ �ʹ� ���� \n");
        exit(1);
    }
    terms[*avail].coef = coef;
    terms[*avail].expon = expon;
    (*avail)++;
}

void poly_multiply(term* A, int As, int Ae, term* B, int Bs, int Be, term* C, int* Csp, int* Cep) {
    int c_start = 0;
    int avail = 0;

    for (int i = As; i <= Ae; i++) {  // ù ��° ���׽��� ��ȸ
        for (int j = Bs; j <= Be; j++) {  // �� ��° ���׽��� ��ȸ
            float coef = A[i].coef * B[j].coef;  // �� ���� ����� ����
            int expon = A[i].expon + B[j].expon;  // �� ���� ������ ����
            // �̹� �ش� ������ ���� �ִ��� Ȯ��
            int already_exists = 0;
            for (int k = c_start; k < avail; k++) {
                if (C[k].expon == expon) {
                    // �̹� �ش� ������ ���� �����ϸ� ����� ����
                    C[k].coef += coef;
                    already_exists = 1;
                    break;
                }
            }
            // �ش� ������ ���� ������ ���� �߰�
            if (!already_exists)
                attach(C, &avail, coef, expon);
        }
    }
    *Csp = c_start;
    *Cep = avail - 1;
}

int main(void) {
    int num_terms1, num_terms2;

    printf("ù ��° ���׽��� �� ���� ���� �Է��Ͻÿ�: ");
    scanf_s("%d", &num_terms1);

    term* poly1 = (term*)malloc(num_terms1 * sizeof(term));
    if (poly1 == NULL) {
        fprintf(stderr, " poly1 ����ü�� �޸𸮰� �����ؼ� �Ҵ��� �� �����ϴ� \n");
        exit(1);
    }

    printf("ù ��° ���׽��� �� �׿� ���� ����� ������ �Է��Ͻÿ�:\n");
    for (int i = 0; i < num_terms1; i++) {
        printf("[���, ����] ");
        scanf_s("%f %d", &(poly1[i].coef), &(poly1[i].expon));
    }

    printf("�Էµ� ���׽��� ������ �����ϴ�: ");
    print_poly(poly1, 0, num_terms1 - 1);

    printf("�� ��° ���׽��� �� ���� ���� �Է��Ͻÿ�: ");
    scanf_s("%d", &num_terms2);

    term* poly2 = (term*)malloc(num_terms2 * sizeof(term));
    if (poly2 == NULL) {
        fprintf(stderr, " poly2 ����ü�� �޸𸮰� �����ؼ� �Ҵ��� �� �����ϴ� \n");
        exit(1);
    }

    printf("�� ��° ���׽��� �� �׿� ���� ����� ������ �Է��Ͻÿ�:\n");
    for (int i = 0; i < num_terms2; i++) {
        printf("[���, ����] ");
        scanf_s("%f %d", &(poly2[i].coef), &(poly2[i].expon));
    }

    printf("�Էµ� ���׽��� ������ �����ϴ�: ");
    print_poly(poly2, 0, num_terms2 - 1);

    int Cs, Ce;
    term* result = (term*)malloc(num_terms1 * num_terms2 * sizeof(term));
    if (result == NULL) {
        fprintf(stderr, " result ����ü�� �޸𸮰� �����ؼ� �Ҵ��� �� �����ϴ� \n");
        exit(1);
    }

    poly_multiply(poly1, 0, num_terms1 - 1, poly2, 0, num_terms2 - 1, result, &Cs, &Ce);

    printf("A*B = ");
    print_poly(result, Cs, Ce);

    free(poly1);
    free(poly2);
    free(result);

    return 0;
}