#include<stdio.h>

int main(void) {
	double x, y, z, valSum, largest;
	printf("세 실수를 과학적 표기법으로 입력해주세요. 구분은 ,(콤마)로 합니다. ");
	scanf("%lf, %lf, %lf", &x, &y, &z);
	valSum = x + y + z;
	largest = (z > (x > y ? x : y) ? z : (x > y ? x : y));
	printf("10진법 표기법으로 표현하면, 합 = %lf, 최대값은 %lf입니다.\n", valSum, largest);
	printf("과학적 표기법으로 표현하면, 합 = %e, 최대값은 %e입니다.  \n", valSum, largest);
	return 0;
}