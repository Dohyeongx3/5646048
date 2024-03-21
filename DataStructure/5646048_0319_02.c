#include<stdio.h>
#include<time.h>

// ¹Ýº¹ °ÅµìÁ¦°ö °è»ê ÇÔ¼ö
long long power_iter(double x, int n) {
	long long result = 1;
	for (int i = 0; i < n; ++i) {
		result = result * x;
	}
	return result;
}

// Àç±Í °ÅµìÁ¦°ö °è»ê ÇÔ¼ö
long long power_rec(double x, int n) {
	if (n == 0) {
		return 1;
	}
	else if ((n % 2) == 0) {
		return power_rec(x * x, n / 2);
	}
	else {
		return x * power_rec(x * x, (n - 1) / 2);
	}
}

int main(void) {
	long long result_iter = power_iter(13, 21);
	long long result_rec = power_rec(13, 21);
	clock_t start_iter, end_iter, start_rec, end_rec;
	double time_iter, time_rec;

	start_iter = clock();
	for (int i = 0; i <= 1000000; i++) {
		power_iter(13,21);
	}
	end_iter = clock();
	time_iter = ((double)(end_iter - start_iter)) / CLOCKS_PER_SEC;
	printf("Power Iterative Result: %llu \n", result_iter);
	printf("Time: %lf \n", time_iter);

	start_rec = clock();
	for (int i = 0; i <= 1000000; i++) {
		power_rec(13, 21);
	}
	end_rec = clock();
	time_rec = ((double)(end_rec - start_rec)) / CLOCKS_PER_SEC;
	printf("Power Recursive Result: %llu \n", result_rec);
	printf("Time: %lf \n", time_rec);

	return 0;
}