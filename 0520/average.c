//산술, 기하, 조화 평균 계산
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//이번 과제의 메인, 각 평균을 구하는 계산 함수
double arithmetic (double x, double y) { printf("산술 평균 계산으로, "); return (x + y) / 2.0; } //산술 평균 계산 함수
double geometric (double x, double y) { printf("기하 평균 계산으로, "); return sqrt(x*y); } //기하 평균 계산 함수
double harmonic (double x, double y) { printf("조화 평균 계산으로, "); return (2.0*x*y) / (x + y); } //조화 평균 계산 함수

//계산 선택을 위한 함수.
void calculator() {
	char mode = 'a';
	double x = 0, y = 0;
	calc_start : //goto 선언
		printf("-----------------\n");
		scanf(" %c, %lf, %lf", &mode, &x, &y); //설명에 버그 관련 언급이 있습니다.
		double calc_result = 0;
		switch (mode) {
			case 'a': calc_result = arithmetic(x, y); break; //산술 평균
			case 'g': calc_result = geometric(x, y); break; //기하 평균
			case 'h': calc_result = harmonic(x, y); break; //조화 평균
			case 'e': printf("프로그램을 종료합니다.\n"); exit(0); break; //프로그램 종료
			default: printf("잘못된 계산을 입력하셨습니다.\n"); goto calc_start; break;//goto는...이건 반성해야 됩니다.
		}
		printf("답은 %lf입니다.\n", calc_result);
}
int main(void) {
	printf("계산 명령, 값1, 값2를 입력해주세요.\n");
	printf("-----------------\n");
	printf("산술 평균 계산 명령은 a\n");
	printf("기하 평균 계산 명령은 g\n");
	printf("조화 평균 계산 명령은 h\n");
	printf("프로그램을 종료하시려면 e를 입력해주세요.\n");
	printf("예시) a,3,3 \n");
	while (1) {
		calculator();
	}
	return 0;
}
