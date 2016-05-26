#include <stdio.h>

int is_factor3(int n) {
	if ((n % 3 == 0) && n) return 1;
	else return 0;
}

int main(void) {
	int i, calc_result = 0;
	for (i = 1; i <= 1000; i++) if (is_factor3(i)) calc_result += i;
	printf("1부터 1000사이의 모든 3의 배수의 합은 %d입니다.\n", calc_result);
	return 0;
}
