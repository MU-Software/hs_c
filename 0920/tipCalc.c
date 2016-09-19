#include<stdio.h>

int main(void) {
	double subtotal, tip, tipRate;
	printf("음식 금액과 팁 비율을 입력해주세요. 구분은 ,(콤마)로 합니다. ");
	scanf("%lf, %lf", &subtotal, &tipRate);//주소 참조
	tip = subtotal * (tipRate / 100);
	printf("팁 금액은 %lf달러이며, 총 금액은 %lf달러입니다.\n", tip, subtotal + tip);
	return 0;
}