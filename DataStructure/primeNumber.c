#include<stdio.h>
#include<stdbool.h>

// �Ҽ� �Ǻ� �Լ�
bool isPrime(int num) {
	if (num <= 1) {
		return false;    // 1 ������ ���� �Ҽ��� �ƴմϴ�.
	}
	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) {
			return false; // �Ҽ��� �ƴմϴ�.
		}
	}
	return true; //�Ҽ� �Դϴ�.
}

int main(void) {
	int sum = 0;
	printf("0���� 100���� �Ҽ�: ");
	for (int i = 0; i <= 100; i++) {
		if (isPrime(i)) {
			sum += i;
			printf("%d ", i);  // 0���� 100���� �Ҽ� ���
		}
	}
	printf("\n0���� 100������ �Ҽ����� ��: %d \n",sum);
	return 0;
}