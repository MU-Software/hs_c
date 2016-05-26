#include <stdio.h>
#include <stdlib.h>

int is_prime(int n)
{
	int i;
	for (i = 2;i<n;i++) if (!(n % i)) break;
	if (i == n) return 1;
	else return 0;
}

int main(void) {
	int i, a, b, tmp;
	printf("입력받은 수 사이에 있는 소수의 개수를 출력합니다.\n");
	printf("수를 반복해서 입력하시면 그 수가 소수인지를 판별해 드립니다.\n\n");
	while (1) {
		int prime_count = 0; //매 루프마다 소수의 개수는 초기화되어야 합니다.
		printf("첫번째 수를 입력하세요.");
		scanf(" %d", &a);
		printf("두번째 수를 입력하세요.");
		scanf(" %d", &b);
		if (a == b) { //만약 첫번째 입력받은 수와 두번쨰 입력받은 수가 같으면
			if (is_prime(a)) printf("%d는 소수입니다.\n\n", a);
			else printf("%d는 소수가 아닙니다.\n\n", a);
			continue; //다시 입력부터 받기
		}
		else if (b < a) { //만약 첫번째로 입력받은 수가 두번째로 입력받은 수보다 크면
			tmp = a; //tmp에 a를 저장하고
			a = b; //a에 b(두번째로 받은 값)를 저장하고
			b = tmp; //b에 tmp값(첫번째로 받은 값)을 저장
		}
		for (i = a; i <= b; i++) if (is_prime(i)) prime_count++; //연산
		printf("%d에서 %d사이에 있는 소수는 총 %d개 입니다.\n\n", a, b, prime_count); //출력
	}
	return 0; //0 반환, 정상 종료
}
