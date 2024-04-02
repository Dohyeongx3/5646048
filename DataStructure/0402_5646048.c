#include<stdio.h>
#include<stdlib.h>

#define MAX_TERMS 101

typedef struct term {
    float coef;
    int expon;
} term;

term terms[MAX_TERMS] = { {4.0,3},{3.0,2},{2.0,1},{1.0,0},
                          {3.0,2},{2.0,1},{8.0,0} };

int avail = 7;

void print_poly(int s, int e) {
    for (int i = s; i < e; i++) {
        printf("%3.1fx^%1d + ", terms[i].coef, terms[i].expon);
    }
    printf("%3.1f\n", terms[e].coef);
}

void attach(float coef, int expon) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "항의 개수가 너무 많음 \n");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

void poly_multiply(int As, int Ae, int Bs, int Be, int* Csp, int* Cep) {
    int c_start = avail;        
    for (int i = As; i <= Ae; i++) {      //첫 번째 다항식을 순회
        for (int j = Bs; j <= Be; j++) {   // 두 번째 다항식을 순회
            float coef = terms[i].coef * terms[j].coef;     // 두 항의 계수를 곱함
            int expon = terms[i].expon + terms[j].expon;     // 두 항의 지수를 더함
            // 이미 해당 지수의 항이 있는지 확인
            int already_exists = 0;
            for (int k = c_start; k < avail; k++) {
                if (terms[k].expon == expon) {
                    // 이미 해당 지수의 항이 존재하면 계수를 더함
                    terms[k].coef += coef;
                    already_exists = 1;
                    break;
                }
            }
            // 해당 지수의 항이 없으면 새로 추가
            if (!already_exists)
                attach(coef, expon);
        }
    }
    *Csp = c_start;
    *Cep = avail - 1;
}

int main(void) {
    int Cs, Ce;
    printf("A = ");
    print_poly(0, 3);
    printf("B = ");
    print_poly(4, 6);

    poly_multiply(0, 3, 4, 6, &Cs, &Ce);
    printf("A*B = ");
    print_poly(Cs, Ce);

    return 0;
}