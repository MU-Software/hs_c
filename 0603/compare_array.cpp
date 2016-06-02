#include <stdio.h>
#define SIZE_ARRAY 5

int array_equal(int a[], int b[], int size) {
	//하나하나씩 비교해서 다르면 0 반환.
	for (int i = 0; i < size; i++) if (a[i] != b[i]) return 0;
	//만약 다 같으면 같다는 의미의 1 반환.
	return 1;
}

int main(void) {
	int array_a[SIZE_ARRAY], array_b[SIZE_ARRAY];
	printf("첫번째 배열의 원소를 입력해 주십시오.\n");
	for (int i = 1; i <= SIZE_ARRAY; i++) {
		printf("%d번째 원소의 값 : ", i);
		scanf("%d", &array_a[i-1]);
	}
	printf("두번째 배열의 원소를 입력해 주십시오.\n");
	for (int i = 1; i <= SIZE_ARRAY; i++) {
		printf("%d번째 원소의 값 : ", i);
		scanf("%d", &array_b[i-1]);
	}
	printf("두개의 배열은 ");
	printf(array_equal(array_a, array_b, SIZE_ARRAY) ? "같습니다.\n" : "다릅니다.\n");
	return 0;
}
