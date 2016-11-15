#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct _user { char id[100] = { 0 }, pw[200] = { 0 }; } user;
user user_info;//사용자 1명만 저장 가능합니다.

void login_success(void) { exit(0); /*로그인에 성공하면 프로그램 종료*/ }

void signin(void) {
	system("cls");
	printf("ID: "); gets_s(user_info.id); rewind(stdin);
	printf("PW: "); gets_s(user_info.pw); rewind(stdin);
	printf("회원가입을 축하합니다!\n");
}

void login(void) {
	system("cls");

	user input_info;
	int fail_count = 0;

	while (1) {
		//FailSafe: 만약 저장된 ID가 없으면 함수를 종료하고 메인으로 이동합니다.
		if (!user_info.id[0]) { printf("저장된 사용자가 없습니다!\n"); return; }

		printf("ID: "); gets_s(input_info.id); rewind(stdin);
		printf("PW: "); gets_s(input_info.pw); rewind(stdin);

		//로그인에 성공했을때
		if (!(strcmp(user_info.id, input_info.id)) && !(strcmp(user_info.pw, input_info.pw))) break;

		//로그인에 실패했을때
		fail_count++;
		printf("로그인에 %d번 실패했습니다!\n", fail_count);
		if (fail_count >= 3) { //로그인에 3번 실패했으면
			printf("프로그램을 종료합니다.\n");
			exit(0);
		}
		printf("비밀번호를 다시 입력해주세요.\n");
	}
	printf("로그인에 성공했습니다, %s님.\n", input_info.id);
	login_success(); //로그인에 성공하면 이 함수가 실행됩니다.
}

int main(void) {
	while (1) {
		int mod = 0;
		printf("1)회원가입  2)로그인\n"); scanf("%d", &mod); rewind(stdin);
		if (mod == 1) signin(); //회원가입
		else login(); //로그인
	}

	return 0;
}