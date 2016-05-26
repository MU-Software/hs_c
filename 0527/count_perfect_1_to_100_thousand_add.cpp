#include <stdio.h>

int is_perfect (int n) {
	int sum2 = 0;
	for (int i = 1; i<n; i++) if (n % i == 0) sum2 += i;
	if (sum2 == n) return 1;
	else return 0;
}

int len_calc(int numInput) {
	int length = 0;
	do {
		numInput = int(numInput / 10);
		length++;
	} while (numInput > 0);
	return length;
}

int main (void) {
	//1에서 10만까지, 만약 is_perfect(i)가 참이면
	for (int i = 1; i <= 100000; i++) if (is_perfect(i)) {
		//i의 약수 출력
		for (int k = 1; k < i; k++) if (!(i % k)) {
			printf(" %d", k);
			//줄맞춤
			for (int lining = 5; lining - len_calc(k) > 0; lining--) putchar(' ');
			//일정한 규칙이 있다.
			printf((i / 2 == k) ? "= " : "+");
		}
		//해당되는 수 출력
		printf("%d\n", i);
	}
	return 0;
}
