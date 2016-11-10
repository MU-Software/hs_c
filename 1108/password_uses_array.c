#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//가능한 특수 문자인지를 판단해주는 함수
int isschar(char input_char){
	if (input_char == '!') return 1;//!
	if (input_char == '#') return 1;//#
	if (input_char == '$') return 1;//$
	if (input_char == '?') return 1;//?
	if (input_char == '@') return 1;//@
	return 0;
}

int issame_more_than_5(char *input_1, char *input_2){
	int count = 0;
	for(int i=0; input_1[i]; i++) {
		for(int j=0; input_2[j]; j++) {
			if (input_1[i+j] == input_2[j]) count++;
			else count = 0;
			
			if (count > 4) return 1;
		}
	}
	return 0;
}

int main(void) {
	char input[100] = { 0 }, password[100] = { 0 };
	while (1) {
		char is_ok[4] = {0};
		int is_str_ok = 0, count = 0;
		//암호 문자열을 저장할 공간을 NULL로 초기화해주고,
		for (int n = 0; n < 100; n++) input[n] = 0;
		printf("설정하실 비밀번호를 입력해주세요. ");
		gets_s(input);//입력을 받습니다.
		
		//연산
		for (count; input[count]; count++){ //여기서 비밀번호의 글자 개수도 세줍니다.
			     if (isupper(input[count]) && !is_ok[0]) is_ok[0] = 1;//대문자인지?
			else if (islower(input[count]) && !is_ok[1]) is_ok[1] = 1;//대문자가 아니면 소문자?
			else if (isdigit(input[count]) && !is_ok[2]) is_ok[2] = 1;//소문자도 아니면 숫자?
			else if (isschar(input[count]) && !is_ok[3]) is_ok[3] = 1;//저것전부 아니면 허용된 특수문자?
		}
		if (count < 9) { printf("비밀번호가 너무 짧습니다. 최소 9자 이상 사용해 주십시오.\n"); continue; }//9글자 이상인지?
		else if (is_str_ok != 15) {//어라, 필요한 글자가 없다?
			if (!is_ok[0]) { printf("대문자를 1개 이상 사용해 주십시오.\n"); continue; }
			if (!is_ok[1]) { printf("소문자를 1개 이상 사용해 주십시오.\n"); continue; }
			if (!is_ok[2]) { printf("숫자를 1개 이상 사용해 주십시오.\n"); continue; }
			if (!is_ok[3]) { printf("특수문자를 1개 이상 사용해 주십시오.\n"); continue; }
		}
		else break;//모든 조건에 맞으므로 While 탈출!
		
	}
	//이제 입력받은 문자열을 저장하고...
	//(물론 실전에서 이렇게 하면 안되고 SHA-3같은걸로 암호화 해줘야합니다.)
	strcpy(password, input);
	printf("Success! Set to '%s'\n", password);//잘 저장되었다고 출력해줍니다.
	
	return 0;//0 반환하고 종료!
}