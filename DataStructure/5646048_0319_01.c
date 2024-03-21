#include<stdio.h>
#include<time.h>

// 반복 팩토리얼 계산 함수
long long factorial_iter(int n) {
	long long result = 1;
	for (int i = 2; i <= n; ++i) {
		result = result * i;
	}
	return(result);
}

// 재귀 팩토리얼 계산 함수
long long factorial_rec(int n) {
	if (n <= 1) {
		return 1;
	}
	else {
		return (n * factorial_rec(n - 1));
	}
}

int main(void) {
	long long result_iter = factorial_iter(20);
	long long result_rec = factorial_rec(20);
	clock_t start_iter, end_iter,start_rec,end_rec;
	double time_iter, time_rec;

	start_iter = clock();
	for (int i = 0; i <= 1000000; i++) {
		factorial_iter(20);
	}
	end_iter = clock();
	time_iter = ((double)(end_iter - start_iter)) / CLOCKS_PER_SEC;
	printf("Factorial Iterative Result: %llu \n", result_iter);
	printf("Time: %lf \n", time_iter);

	start_rec = clock();
	for (int i = 0; i <= 1000000; i++) {
		factorial_rec(20);
	}
	end_rec = clock();
	time_rec = ((double)(end_rec - start_rec)) / CLOCKS_PER_SEC;
	printf("Factorial Recursive Result: %llu \n", result_rec);
	printf("Time: %lf \n", time_rec);

	return 0;
}