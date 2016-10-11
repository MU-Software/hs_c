#include<stdio.h>
#define INT_CMP(x, y) ((x) > (y) ? (x) : (y))

int int_cmp(int x, int y) {
	if (x > y) return x;
	return y;
}

int main(void) {
	int a, b, c, highest;
	printf("세 수를 입력해 주십시오. 쉼표(,)로 구분합니다.\n");
	scanf("%d, %d, %d", &a, &b, &c);
	highest = int_cmp(c, INT_CMP(a, b));
	printf("입력받은 값 중 최대값은 %d입니다.", highest);
	return 0;
}
