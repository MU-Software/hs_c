#include <stdio.h>
#include <limits.h>

int main(void) {
	int input, highest = INT_MIN, highest_count = 0;
	while (1) {
		if (scanf("%d", &input) == EOF) break;
		if (input > highest) {
			highest = input;
			highest_count = 1;
		}
		else if (input == highest) highest_count++;
	}
	printf("입력받은 수 중 가장 큰 수는 %d고, %d번 나왔습니다.\n", highest, highest_count);
	return 0;
}
