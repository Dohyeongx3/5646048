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
        fprintf(stderr, "항의 개수가 너무 많음 \n");
        exit(1);
    }
    terms[*avail].coef = coef;
    terms[*avail].expon = expon;
    (*avail)++;
}

void poly_multiply(term* A, int As, int Ae, term* B, int Bs, int Be, term* C, int* Csp, int* Cep) {
    int c_start = 0;
    int avail = 0;

    for (int i = As; i <= Ae; i++) {  // 첫 번째 다항식을 순회
        for (int j = Bs; j <= Be; j++) {  // 두 번째 다항식을 순회
            float coef = A[i].coef * B[j].coef;  // 두 항의 계수를 곱함
            int expon = A[i].expon + B[j].expon;  // 두 항의 지수를 더함
            // 이미 해당 지수의 항이 있는지 확인
            int already_exists = 0;
            for (int k = c_start; k < avail; k++) {
                if (C[k].expon == expon) {
                    // 이미 해당 지수의 항이 존재하면 계수를 더함
                    C[k].coef += coef;
                    already_exists = 1;
                    break;
                }
            }
            // 해당 지수의 항이 없으면 새로 추가
            if (!already_exists)
                attach(C, &avail, coef, expon);
        }
    }
    *Csp = c_start;
    *Cep = avail - 1;
}

int main(void) {
    int num_terms1, num_terms2;

    printf("첫 번째 다항식의 총 항의 수를 입력하시오: ");
    scanf_s("%d", &num_terms1);

    term* poly1 = (term*)malloc(num_terms1 * sizeof(term));
    if (poly1 == NULL) {
        fprintf(stderr, " poly1 구조체를 메모리가 부족해서 할당할 수 없습니다 \n");
        exit(1);
    }

    printf("첫 번째 다항식의 각 항에 대해 계수와 차수를 입력하시오:\n");
    for (int i = 0; i < num_terms1; i++) {
        printf("[계수, 차수] ");
        scanf_s("%f %d", &(poly1[i].coef), &(poly1[i].expon));
    }

    printf("입력된 다항식은 다음과 같습니다: ");
    print_poly(poly1, 0, num_terms1 - 1);

    printf("두 번째 다항식의 총 항의 수를 입력하시오: ");
    scanf_s("%d", &num_terms2);

    term* poly2 = (term*)malloc(num_terms2 * sizeof(term));
    if (poly2 == NULL) {
        fprintf(stderr, " poly2 구조체를 메모리가 부족해서 할당할 수 없습니다 \n");
        exit(1);
    }

    printf("두 번째 다항식의 각 항에 대해 계수와 차수를 입력하시오:\n");
    for (int i = 0; i < num_terms2; i++) {
        printf("[계수, 차수] ");
        scanf_s("%f %d", &(poly2[i].coef), &(poly2[i].expon));
    }

    printf("입력된 다항식은 다음과 같습니다: ");
    print_poly(poly2, 0, num_terms2 - 1);

    int Cs, Ce;
    term* result = (term*)malloc(num_terms1 * num_terms2 * sizeof(term));
    if (result == NULL) {
        fprintf(stderr, " result 구조체를 메모리가 부족해서 할당할 수 없습니다 \n");
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