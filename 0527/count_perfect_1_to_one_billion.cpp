#include <stdio.h>

int is_perfect (int n) {
	int sum2 = 0;
	for (int i = 1; i<n; i++) if (n % i == 0) sum2 += i;
	if (sum2 == n) return 1;
	else return 0;
}

int main (void) {
	//1에서 10만까지, 만약 is_perfect(i)가 참이면
	for (int i = 1; i <= 100000; i++) if (is_perfect(i)) printf("%d  \n", i);
	return 0;
}
