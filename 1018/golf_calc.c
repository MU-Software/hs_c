#include<stdio.h>
#define GOLF_COURSE 18
#define LINE_DASH 100

void line_printer(void) { for (int i = 0; i < LINE_DASH; i++) printf(i == LINE_DASH-1 || !i ? "\n" : "-"); }

int main(void) {
	//정의
	int par_score[GOLF_COURSE]    = { 4, 5, 3, 4, 5, 4, 3, 4, 4, 4, 5, 3, 4, 4, 4, 5, 3, 4 };
	int player_score[GOLF_COURSE] = { 0 }, score_status[GOLF_COURSE] = { 0 }, score_status_case[7] = { 0 };
	//score_status_case 0: 알바트로스, 1: 이글, 2: 버디, 3: 파, 4:보기, 5:더블보기, 6:트리플보기

	//입력
	for (int i = 0; i < GOLF_COURSE; i++) { printf("[%2d] ", i+1); scanf("%d", &player_score[i]); }

	//연산
	for (int i = 0; i < GOLF_COURSE; i++) {
		int tmp = player_score[i] - par_score[i];
		//score_status[-1] 방지용
		if (i != 0) score_status[i] = tmp + score_status[i - 1];
		if (tmp <= -3) score_status_case[0]++;

		else if (tmp == -2) score_status_case[1]++;
		else if (tmp == -1) score_status_case[2]++;
		else if (tmp == 0) score_status_case[3]++;
		else if (tmp == 1) score_status_case[4]++;
		else if (tmp == 2) score_status_case[5]++;
		else { score_status_case[6]++; }
	}

	//출력
	line_printer();
	printf("Hole   : "); for (int i = 0; i < GOLF_COURSE; i++) printf("%4d", i+1);
	line_printer();
	printf("Par    : "); for (int i = 0; i < GOLF_COURSE; i++) printf("%4d", par_score[i]);
	line_printer();
	printf("Score  : "); for (int i = 0; i < GOLF_COURSE; i++) printf("%4d", player_score[i]);
	line_printer();
	printf("Status : "); for (int i = 0; i < GOLF_COURSE; i++) printf(score_status[i]? "%+4d" : "   E", score_status[i]);
	line_printer();
	printf("   알바트로스 : %d\n", score_status_case[0]);
	printf("         이글 : %d\n", score_status_case[1]);
	printf("         버디 : %d\n", score_status_case[2]);
	printf("           파 : %d\n", score_status_case[3]);
	printf("         보기 : %d\n", score_status_case[4]);
	printf("     더블보기 : %d\n", score_status_case[5]);
	printf("  트리플보기+ : %d\n", score_status_case[6]);
	return 0;
}