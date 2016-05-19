//2의 제곱 계산
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//이번 과제의 메인, 각 평균을 구하는 계산 함수
//어차피 2의 n승에서 소수가 나올 일이 없으니 정수로 반환합니다.
int power_2 (int input) { return pow ((double)2, input); }

int main (void) {
	int cal = 1, i;
	for (i=1; cal < 32768; i++) {//cal이 32768이 나올때까지.
		cal = power_2(i);
		printf("%d는 2의 %d제곱입니다.\n", cal, i);
	}
	return 0;//0 반환, 프로그램 무사 종료.
}