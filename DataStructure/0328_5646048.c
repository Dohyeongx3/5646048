#include<stdio.h>
#define MAX_DEGREE 101


typedef struct polynomial { // ���׽� ����ü
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

// �� ���׽��� ���ϴ� �Լ�
polynomial multiply_polynomial(polynomial A, polynomial B) {
	polynomial result;
	result.degree = A.degree + B.degree; // ��� ���׽��� ������ �� ���׽��� ������ ��
	
	for (int i = 0; i <= result.degree; i++) // ��� ���׽��� ��� �迭 �ʱ�ȭ
		result.coef[i] = 0;
	
	for (int i = 0; i <= A.degree; i++) {     // ���׽� ���� �˰����� ���� ��� ���׽� ���
		for (int j = 0; j <= B.degree; j++) {
			result.coef[i + j] += A.coef[i] * B.coef[j];
		}
	}

	return result;
}

// ���׽� ����Լ�
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

	printf("1�� ����: \n");
	print_polynomial(a);
	print_polynomial(b);
	r1 = multiply_polynomial(a, b);
	printf("-------------------------------------------------------------------------\n");
	print_polynomial(r1);
	printf("\n");

	printf("2�� ����: \n");
	print_polynomial(c);
	print_polynomial(d);
	r2 = multiply_polynomial(c, d);
	printf("-------------------------------------------------------------------------\n");
	print_polynomial(r2);

	return 0;
}