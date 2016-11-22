#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define USER_COUNT 255
//기본 필수 자료형[available: 사용 가능한 자료인지 표기, name: 이름, num: 전화번호]
typedef struct _user { int available = 0; char name[20]; char num[20]; } user;
void user_add(user *array, const int index);
void user_del(user *array, const int index);
void print_all(user *array, const int index);
void print_search(user *array, const int index);
int user_struct_compare_name(const void *a, const void *b);
int user_struct_compare_num(const void *a, const void *b);
int user_search_num(user *array, const int index, const char *input_num);
int user_search_name(user *array, const int index, const char *input_name);
void sort_array(user *array, const int index);

void user_add(user *array, const int index) {
	rewind(stdin);
	char input_name[20] = { 0 }, input_num[20] = { 0 };
	printf("저장할 이름을 입력해 주세요: "); gets_s(input_name);
	printf("전화번호를 입력해 주세요  : "); gets_s(input_num);
	if (user_search_name(array, index, input_name) > -1) {
		printf("이미 겹치는 이름이 있습니다.\n저장을 취소합니다.\n");
		return;
	}
	if (user_search_num(array, index, input_num) > -1) {
		printf("이미 겹치는 전화번호가 있습니다.\n저장을 취소합니다.\n");
		return;
	}
	for (int i = 0; i < index; i++) if (!((array + i)->available)) {
		strcpy((array + i)->name, input_name);
		strcpy((array + i)->num, input_num);
		(array + i)->available = 1;
		printf("전화번호부 %d번에 %s 님의 전화번호(%s)를 저장했습니다.", i, input_name, input_num);
		return;
	}
	printf("전화번호부에 저장할 공간이 없습니다.\n저장하지 못했습니다.\n");
	return;
}
void user_del(user *array, const int index) {
	int mod = 0, result = -1;
	char input_str[20] = { 0 };
	while (1) {
		printf("1) 이름으로 찾기 2) 전화번호로 찾기\n"); scanf(" %d", &mod);
		if (0 < mod && mod < 3) break;
		else printf("잘못 선택하셨습니다.\n");
		mod = 0;
	}
	rewind(stdin);
	if (mod == 1) {
		printf("삭제할 이름을 입력해 주세요: "); gets_s(input_str);
		result = user_search_name(array, index, input_str);
	}
	else if (mod == 2) {
		printf("삭제할 전화번호를 입력해 주세요  : "); gets_s(input_str);
		result = user_search_num(array, index, input_str);
	}
	else return;
	rewind(stdin);
	if (result == -1) { printf("존재하지 않는 사용자입니다.\n"); return; }
	else {
		printf("%s 님의 정보를 삭제합니다. 계속하시겠습니까?(Y/N)\n", (array + result)->name);
		int check_del = getchar();
		if (check_del == 'Y' || check_del == 'y') {
			(array + result)->available = 0;
			printf("삭제되었습니다.\n");
		}
		else printf("삭제 작업이 취소되었습니다.\n");
		return;
	}
}
int user_search_name(user *array, const int index, const char *input_name) {
	for (int i = 0; i < index; i++)
		if ((array + i)->available)
			if (!(strcmp((array + i)->name, input_name)))
				return i;
	return -1;//못찾으면 -1 반환
}
int user_search_num(user *array, const int index, const char *input_num) {
	for (int i = 0; i < index; i++)
		if ((array + i)->available)
			if (!(strcmp((array + i)->num, input_num)))
				return i;
	return -1;//못찾으면 -1 반환
}
void print_search(user *array, const int index) {
	int mod = 0, result = -1;
	char input_str[20] = { 0 };
	while (1) {
		printf("1) 이름으로 찾기 2) 전화번호로 찾기\n"); scanf(" %d", &mod);
		if (0 < mod && mod < 3) break;
		else printf("잘못 선택하셨습니다.\n");
		mod = 0;
	}
	rewind(stdin);
	if (mod == 1) {
		printf("검색할 이름을 입력해 주세요: "); gets_s(input_str);
		result = user_search_name(array, index, input_str);
	}
	else if (mod == 2) {
		printf("검색할 전화번호를 입력해 주세요  : "); gets_s(input_str);
		result = user_search_num(array, index, input_str);
	}
	else return;
	rewind(stdin);
	if (result == -1) { printf("존재하지 않는 사용자입니다.\n"); return; }
	else {
		printf("      이름    |     전화번호 \n");
		printf(" %10s   | %14s \n", (array + result)->name, (array + result)->num);
	}
}
void print_all(user *array, const int index) {
	printf("      이름    |     전화번호 \n");
	for (int i = 0; i < index; i++)
		if ((array + i)->available)
			printf(" %10s   | %14s \n", (array + i)->name, (array + i)->num);
}
int user_struct_compare_name(const void *a, const void *b) {
	user *ptrA = (user*)a;
	user *ptrB = (user*)b;
	return strcmp((char *)ptrA->name, (char *)ptrB->name);
}
int user_struct_compare_num(const void *a, const void *b) {
	user *ptrA = (user*)a;
	user *ptrB = (user*)b;
	return strcmp((char *)ptrA->num, (char *)ptrB->num);
}
void sort_array(user *array, const int index) {
	int mod = 0, result = -1;
	char input_str[20] = { 0 };
	while (1) {
		printf("1) 이름으로 정렬 2) 전화번호로 정렬\n"); scanf(" %d", &mod);
		if (0 < mod && mod < 3) break;
		else printf("잘못 선택하셨습니다.\n");
		mod = 0;
	}
	rewind(stdin);
	if (mod == 1) {
		qsort(array, index, sizeof(user), user_struct_compare_name);
	}
	else if (mod == 2) {
		qsort(array, index, sizeof(user), user_struct_compare_num);
	}
	else return;
	rewind(stdin);
}

int main(void) {
	int choice = 0;
	user PhoneBook[USER_COUNT];
	while (1) {
		system("cls");
		printf("1) 입력\n");
		printf("2) 삭제\n");
		printf("3) 검색\n");
		printf("4) 전체 출력\n");
		printf("5) 정렬 후 출력\n");
		printf("6) 종료\n");
		printf("원하는 번호를 선택하세요 : ");
		scanf("%d", &choice);
		system("cls");
		switch (choice) {
		case 1:
			printf("입력 선택\n");
			user_add(PhoneBook, USER_COUNT);
			break;
		case 2:
			printf("삭제 선택\n");
			user_del(PhoneBook, USER_COUNT);
			break;
		case 3:
			printf("검색 선택\n");
			print_search(PhoneBook, USER_COUNT);
			break;
		case 4:
			printf("출력 선택\n");
			print_all(PhoneBook, USER_COUNT);
			break;
		case 5:
			printf("정렬 선택\n");
			sort_array(PhoneBook, USER_COUNT);
			print_all(PhoneBook, USER_COUNT);
			break;
		case 6:
			printf("프로그램을 종료합니다.\n");
			exit(0);
			break;
		default:
			printf("잘못 선택하셨습니다.\n");
			break;
		}
		rewind(stdin); getchar();
	}
	return 0;
}