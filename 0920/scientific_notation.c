/*
전 소스코드도 동작은 합니다만, 과제 문제의 출제의도를 생각하면 이것이 더 정확하므로 수정합니다.
죄송해요ㅠㅜ
*/
#include<stdio.h>

int main(void) {
	double x, y, z, valSum, largest;
	printf("세 실수를 과학적 표기법으로 입력해주세요. 구분은 ,(콤마)로 합니다. ");
	//lf로도 받을 수 있지만, 과학적 표기법으로 확실히 받는 것이기 때문에 le로 수정합니다.
	scanf("%le, %le, %le", &x, &y, &z);
	valSum = x + y + z;
	largest = (z > (x > y ? x : y) ? z : (x > y ? x : y));
	printf("10진법 표기법으로 표현하면, 합 = %lf, 최대값은 %lf입니다.\n", valSum, largest);
	//e로도 출력할 수 있지만, double이기 때문에 le로 수정합니다.
	printf("과학적 표기법으로 표현하면, 합 = %le, 최대값은 %le입니다.  \n", valSum, largest);
	return 0;
}