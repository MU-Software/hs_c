#include <stdio.h>
#include <math.h>

int main(void) {
	double n = 100, i, pie = 0;
	for (n; n <= 1000000; n *= 10) {
		pie = 0;
		for (i = 1; i <= n; i++) {
			pie += 4 * ( pow(-1, i + 1) / ((2 * i) - 1) );
		}
		printf("%7.lf    %lf\n", n, pie);
	}
	return 0;
}