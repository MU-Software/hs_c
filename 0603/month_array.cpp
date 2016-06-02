#include <stdio.h>

int main (void) {
	int days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for (int i = 1; i <= 12; i++) printf("%d월은 %d일까지 있습니다.\n", i, days[i-1]);
	return 0;
}
