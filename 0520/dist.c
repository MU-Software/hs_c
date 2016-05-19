//점 2개의 거리 계산
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//2차원의 점은 x와 y를 값으로 가집니다.
typedef struct _values { double x; double y; } pointPos;

//2개의 2차원 위치를 받아서 거리를 반환합니다.
double dist_calc(pointPos a, pointPos b) {
	double dist = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	//2개 점의 거리를 구하는 것이니 0을 포함한 양수만 나와야합니다.
	if (dist < 0) dist = -dist;
	//거리 반환
	return dist;
}

int main(void) {
	pointPos point_1, point_2; //변수 정의
	printf("점 2개의 거리를 계산합니다.\n");
	printf("종료하시려면 키보드 인터럽트(ctrl + c)를 걸어주십시오.\n");
	while (1) { //무한 반복
		printf("--------------------\n");
		printf("첫번째 점의 x,y 좌표를 입력하세요. 콤마(,)로 구분합니다. ");
		scanf("%lf, %lf", &point_1.x, &point_1.y); //점 point_1의 x, y
		printf("두번째 점의 x,y 좌표를 입력하세요. 콤마(,)로 구분합니다. ");
		scanf("%lf, %lf", &point_2.x, &point_2.y); //점 point_2의 x, y
												   //연산 & 출력
		printf("두 점의 거리는 %lf입니다.\n", dist_calc(point_1, point_2));
	}
	return 0;//0 반환, 프로그램 무사 종료.
}
