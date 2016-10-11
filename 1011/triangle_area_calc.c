#include<stdio.h>
#include<math.h>
//2차원 벡터에 대한 구조체
typedef struct _vec2 { double x; double y; } vec2;

//두 점의 거리를 구하는 함수
double dist(vec2 p1, vec2 p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

//삼각형을 검증하는 함수
int is_triangle(vec2 p1, vec2 p2, vec2 p3) {
	double s1 = dist(p1, p2), s2 = dist(p2, p3), s3 = dist(p1, p3);
	if (s1 + s2 <= s3) return 0;
	if (s1 + s3 <= s2) return 0;
	if (s2 + s3 <= s1) return 0;
	return 1;
}

//삼각형의 넓이를 구하는 함수
double triangle_area(vec2 p1, vec2 p2, vec2 p3) {
	double size, s1 = dist(p1, p2), s2 = dist(p2, p3), s3 = dist(p1, p3);
	double s = (s1 + s2 + s3) / 2;
	size = sqrt(s*(s - s1)*(s - s2)*(s - s3));
	return size;
}

//점과 점 사이의 거리를 출력해주는 함수
void prt_dist(vec2 p1, vec2 p2) {
	printf("(%lf, %lf)와 (%lf, %lf)사이의 거리는 %lf입니다.\n", p1.x, p1.y, p2.x, p2.y, dist(p1, p2));
}

int main(void) {
	vec2 point_1, point_2, point_3;
	printf("첫번째 점의 좌표를 입력해주세요. 콤마(,)로 구분합니다.\n예) 15, 23\n");
	scanf("%lf, %lf", &point_1.x, &point_1.y);
	printf("두번째 점의 좌표를 입력해주세요.");
	scanf("%lf, %lf", &point_2.x, &point_2.y);
	printf("마지막 점의 좌표를 입력해주세요.");
	scanf("%lf, %lf", &point_3.x, &point_3.y);

	//세 변의 길이 출력
	prt_dist(point_1, point_2);
	prt_dist(point_1, point_3);
	prt_dist(point_2, point_3);

	//얘네 삼각형 맞나요?
	printf("삼각형이 ");
	printf(is_triangle(point_1, point_2, point_3) ? "맞습니다.\n" : "아닙니다.\n");

	//그래서 삼각형의 넓이는요?
	if(is_triangle(point_1, point_2, point_3))//삼각형이 맞을 때에만 출력합니다.
		printf("이 삼각형의 넓이는 %lf입니다.\n", triangle_area(point_1, point_2, point_3));

	return 0;
}