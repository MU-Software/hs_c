#include <stdio.h>
#include <math.h>

double factorial(int n);

int main(void) {
	double result = 0;
	for (int i = 0; i < 10000; i++) result += 1 / factorial(i);
	printf("오일러의 수 계산 결과 = %lf\n", result);
	return 0;
}

double factorial(int n) {
	double result = 1.0f;
	for (int i = n; i > 0; i--) result *= i;
	return result;
}