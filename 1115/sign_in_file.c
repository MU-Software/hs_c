#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	int fail_count = 0;
	char password[] = { "unexpected8090" }, input[100] = { 0 };
	while (1) {
		printf("비밀번호를 입력해주세요.\n");
		gets_s(input);

		//로그인에 성공했을때
		if (!(strcmp(password, input))) break;

		//로그인에 실패했을때
		fail_count++;
		printf("로그인에 %d번 실패했습니다!\n", fail_count);
		if (fail_count >= 3) { //로그인에 3번 실패했으면
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		printf("비밀번호를 다시 입력해주세요.\n");
	}
	do_something();
	return 0;
}