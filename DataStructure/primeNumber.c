#include<stdio.h>
#include<stdbool.h>

// 소수 판별 함수
bool isPrime(int num) {
	if (num <= 1) {
		return false;    // 1 이하의 수는 소수가 아닙니다.
	}
	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) {
			return false; // 소수가 아닙니다.
		}
	}
	return true; //소수 입니다.
}

int main(void) {
	int sum = 0;
	printf("0부터 100까지 소수: ");
	for (int i = 0; i <= 100; i++) {
		if (isPrime(i)) {
			sum += i;
			printf("%d ", i);  // 0부터 100까지 소수 출력
		}
	}
	printf("\n0부터 100까지의 소수들의 합: %d \n",sum);
	return 0;
}