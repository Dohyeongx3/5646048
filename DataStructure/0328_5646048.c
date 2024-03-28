#include<stdio.h>
#define MAX_DEGREE 101


typedef struct polynomial { // 다항식 구조체
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

// 두 다항식을 곱하는 함수
polynomial multiply_polynomial(polynomial A, polynomial B) {
	polynomial result;
	result.degree = A.degree + B.degree; // 결과 다항식의 차수는 두 다항식의 차수의 합
	
	for (int i = 0; i <= result.degree; i++) // 결과 다항식의 계수 배열 초기화
		result.coef[i] = 0;
	
	for (int i = 0; i <= A.degree; i++) {     // 다항식 곱셈 알고리즘을 통해 결과 다항식 계산
		for (int j = 0; j <= B.degree; j++) {
			result.coef[i + j] += A.coef[i] * B.coef[j];
		}
	}

	return result;
}

// 다항식 출력함수
void print_polynomial(polynomial p) {
	for (int i = p.degree; i > 0; i = i - 1) {
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1f \n", p.coef[p.degree]);
}

int main(void) {
	polynomial a = { 3,{4.0,3.0,2.0,1.0} };
	polynomial b = { 2,{3.0,2.0,8.0,} };
	polynomial c = { 6,{7.0,0.0,0.0,5.0,9.0,0.0,1.0} };
	polynomial d = { 3,{5.0,2.0,1.0,10.0} };
	polynomial r1,r2;

	printf("1번 문제: \n");
	print_polynomial(a);
	print_polynomial(b);
	r1 = multiply_polynomial(a, b);
	printf("-------------------------------------------------------------------------\n");
	print_polynomial(r1);
	printf("\n");

	printf("2번 문제: \n");
	print_polynomial(c);
	print_polynomial(d);
	r2 = multiply_polynomial(c, d);
	printf("-------------------------------------------------------------------------\n");
	print_polynomial(r2);

	return 0;
}