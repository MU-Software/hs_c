#include<stdio.h>
#define FREE_TIME 30
#define COUNT_PER_MIN 30
//개장 시간과 폐장 시간. HOUR * 60 + MIN입니다.
#define OPEN_TIME 570 //9시 30분
#define CLOSE_TIME 1410 //23시 30분

int main(void) {
	int in_h, in_m, out_h, out_m, in_time, pay = 0;
	printf("[들어온 시간:분, 온 시간:분]을 입력해주세요.\n");
	printf("예시) 12:30, 12:48\n");
	scanf("%d: %d, %d: %d", &in_h, &in_m, &out_h, &out_m);
	in_time = ((out_h - in_h) * 60) + (out_m - in_m);
	if (in_time < 0) { printf("Input Error.여긴 하루만 주차 가능합니다.\n"); return 0; }
	if (in_time > FREE_TIME) {
		pay = (in_time - 30) / COUNT_PER_MIN;
		pay += (((in_time - 30) % COUNT_PER_MIN) ? 1 : 0);
		pay *= 1000;
	}

	printf("%d분(%d시간 %d분) 계셨고,", in_time, in_time / 60, in_time % 60);
	printf(pay ? " %d원 내셔야합니다.\n" : " 내실 금액은 없습니다.\n", pay);

	if ((in_h * 60 + in_m) < OPEN_TIME) printf("개장 시간 전인데 들어오실 수 있어요?\n");
	if (((in_h * 60 + in_m) < OPEN_TIME) && ((out_h * 60 + out_m) > CLOSE_TIME))
		printf("그리고 ");
	if ((out_h * 60 + out_m) > CLOSE_TIME) printf("폐장 시간 후인데 나가실 수 있어요?\n");

	return 0;
}