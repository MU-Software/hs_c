#include<stdio.h>

int main(void) {
	double di, t, h;
	printf("온도와 습도를 입력해주세요. 콤마( , )로 구분합니다.\n");
	while(1){
		scanf("%lf, %lf", &t, &h);
		di = (9 * t / 5) - (0.55 * (1 - h) * ((9 * t / 5) - 26)) + 32;
		
		printf("현재 불쾌지수는 %.2lf이며, \n", di);
		printf("불쾌단계 ");
		if      (di < 68) printf("낮음");
		else if (di < 75) printf("보통");
		else if (di < 80) printf("높음");
		else printf("매우 높음");
		printf(" 상태입니다.\n");
		rewind(stdin);
	}
	return 0;
}