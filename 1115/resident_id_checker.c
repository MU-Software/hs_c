#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isvalid_id(const char *input_str) {//무슨일이 있어도 변형되면 안되므로 const
	char tmp_charset[15] = { 0 };
	int total = 0, magic_array[] = { 2, 3, 4, 5, 6, 7, 0, 8, 9, 2, 3, 4, 5 };
	for (int i = 0; i<13; i++) if (input_str[i] >= 0) {
		tmp_charset[i] = input_str[i]*magic_array[i];
		total += tmp_charset[i];
	}
	if (11 - (total % 11) == input_str[13]) return 1;
	return 0;
}

int isvalid_date(int year, int month, int day) {
	int year_leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
	switch (month) {
		//1, 3, 5, 7, 8, 10, 12월은 31일까지.
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: if (day <= 31) return 1; break;
		//4, 6, 9, 11월은 30일까지.
		case 4: case 6: case 9: case 11: if (day <= 30) return 1; break;
		//2월. 윤년이면 year_leap가 true이므로 29일, 아니면 28일.
		case 2: return (day <= (year_leap) ? 29 : 28); break;
		//month값이 1 - 12가 아닌 경우.
		default: break;
	}
	return 0;
}

int main(void) {
	char user_id[15] = { 0 }, gender = 0;
	printf("주민등록번호를 -를 포함하여 입력하시오. "); gets_s(user_id);

	if (strlen(user_id) != 14) { printf("주민등록번호의 길이가 너무 짧습니다.\n"); return 0; }//길이 확인

	for (int i = 0; user_id[i]; i++) user_id[i] -= '0';//교수님의 추천 방법대로 숫자 배열로 바꿉니다.
	int year = user_id[0] * 10 + user_id[1], month = user_id[2] * 10 + user_id[3], day = user_id[4] * 10 + user_id[5];
	gender = user_id[7];
	if (gender == 1 || gender == 2) year += 1900; else year += 2000; //1900년대인지, 2000년대인지 확인

	if (!((gender <= 4) && (gender > 0))) { printf("주민등록번호의 성별이 유효하지 않습니다.\n"); return 0; }//유효성 확인
	if (!isvalid_date(year, month, day)) { printf("주민등록번호의 생년월일이 유효하지 않습니다.\n"); return 0; }//날짜 확인
	if (!isvalid_id(user_id)) { printf("유효하지 않은 주민등록번호입니다.\n"); return 0; }//유효성 확인

	//출력
		 if (gender == 1 || gender == 3) printf("남성, ");
	else if (gender == 2 || gender == 4) printf("여성, ");
	printf("%d년 %d월 %d일생 입니다.\n", year, month, day);

	return 0;
}