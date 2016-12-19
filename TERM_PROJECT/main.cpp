/*
MUsoftware DB imitation Project
Written by MUsoftware
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct _user {
	int available = 0;
	char id[255];
	char pw[255];
	char name[255];
	int level;
	double score;
	char **addon_data;
} user;

void menu(void);
char *rtrim(char* s);
char *ltrim(char* s);
char *trim(char* s);
user *file_to_data(int *user_index_p, int *addon_index_p, char ***addon_name_p);
void data_to_file(user *user_data, int user_count, char **addon_name, int addon_count);
void printAll(user *user_data, int user_count, char **addon_name, int addon_count, FILE *outPoint);
void print(user user_info);
int cmp_score(const void *x, const void *y);
int cmp_level(const void *x, const void *y);
void sort(user user_data[], int user_index);
int search_id(user *user_data, int user_count, char *id);
int search_name(user *user_data, int user_count, char *name);
void search(user *user_data, int user_count);
void del_user(user *user_data, int user_index);
void fix_info(user *user_data, int user_index, char **addon_name, int addon_index);
void add_column(user *user_data[], int user_index, char ***addon_name_p, int *addon_index_p);
void exit_prog(void);

char *rtrim(char* s) {
	char t[4096];
	char *end;

	strcpy(t, s);
	end = t + strlen(t) - 1;
	while (end != t && isspace(*end)) end--;
	*(end + 1) = '\0';
	s = t;

	return s;
}
char *ltrim(char *s) {
	char* begin;
	begin = s;

	while (*begin != '\0') {
		if (isspace(*begin)) begin++;
		else {
			s = begin;
			break;
		}
	}

	return s;
}
char *trim(char *s) {
	return rtrim(ltrim(s));
}
user *file_to_data(int *user_index_p, int *addon_index_p, char ***addon_name_p) {
	printf("파일로부터 정보를 읽어옵니다.\n");
	int line_counter = 0;
	int column_index = 0;
	char str_buf[255] = { 0 };

	char fpath[255] = { 0 };
	printf("DB 파일의 경로를 입력해 주세요.\n"); gets_s(fpath); rewind(stdin);
	FILE *file_open = fopen(fpath, "r");
	//FILE *file_open = fopen("datafile.txt", "r");
	if (file_open == NULL) { printf("파일을 열 수 없습니다!\n프로그램을 종료합니다.\n"); exit(0); }

	//파일 검증
	for (line_counter; !feof(file_open); line_counter++) {
		fgets(str_buf, (int)sizeof(str_buf), file_open);//파일 한 줄 읽기
		strtok(str_buf, "\n");//한 줄 읽은 것에서 맨 마지막 줄바꿈을 없애줍니다.

		//첫번째 줄
		if (!line_counter) {
			char *tmp_ptr = str_buf;
			while ((tmp_ptr = strpbrk(tmp_ptr, "|")) != NULL) {
				column_index++;
				tmp_ptr++;
			}
			if (column_index < 4) {
				printf("데이터 파일이 손상되었습니다.(NEED_MORE_COLUMN)\n프로그램을 종료합니다.\n");
				exit(0);
			}
			continue;
		}
		//그 외의 다른 줄
		int check_addon_data = 0;
		char *tmp_ptr = str_buf;
		//만약 중간에 데이터가 없거나 마지막이 구분자로 끝나면
		if (strstr(str_buf, "||") != NULL || str_buf[(strlen(str_buf) - 1)] == '|') {
			printf("데이터 파일이 손상되었습니다.(NULL_COLUMN_DATA)\n프로그램을 종료합니다.\n");
			exit(0);
		}
		while ((tmp_ptr = strpbrk(tmp_ptr, "|")) != NULL) {
			check_addon_data++;
			tmp_ptr++;
		}
		if (check_addon_data != column_index) {
			printf("데이터 파일이 손상되었습니다.(DISCORDANCE_BETWEEN_NAME_AND_DATA)\n프로그램을 종료합니다.\n");
			exit(0);
		}
	}

	column_index++;
	int user_count = line_counter -= 2;
	int addon_count = column_index - 5;
	user *file_data = (user*)malloc(user_count * sizeof(user));
	for (int z = 0; z < user_count; z++) {
		(file_data + z)->addon_data = (char**)malloc(sizeof(char*) * addon_count);
		for (int x = 0; x < addon_count; x++) {
			(file_data + z)->addon_data[x] = (char*)calloc(1, 255*sizeof(char));
		}
	}
	char **addon_name = NULL;
	if (addon_count > 0) {
		addon_name = (char **)calloc(1, sizeof(char*) * addon_count);
		addon_name[0] = (char *)calloc(1, sizeof(char) * 255 * addon_count);
		for (int i = 1; i < addon_count; i++) addon_name[i] = addon_name[i - 1] + 255;
	}
	else addon_count = 0;

	rewind(file_open);//파일의 처음으로
	//파일을 메모리에 올리기
	for (int z = -1; z < user_count; z++) {
		char tmp_data_str[255] = { 0 };
		user *tmp_user_ptr = NULL;
		strcpy(str_buf, "");
		fgets(str_buf, (int)sizeof(str_buf), file_open);
		while ((str_buf[strlen(str_buf) - 1]) == '\n') strtok(str_buf, "\n");
		if (!(strcmp(str_buf, ""))) continue;

		//첫줄 애드온 이름 라벨
		if (z == -1) {
			if (addon_count) for (int y = 0; y < addon_count + 5; y++) {
				strcpy(tmp_data_str, (!y ? strtok(str_buf, "|") : strtok(0, "|")));
				if (y > 4) {
					strcpy(addon_name[y - 5], trim(tmp_data_str));
				}
			}
			continue;
		}
		
		for (int y = 0; y < addon_count + 5; y++) if (str_buf != NULL || str_buf != "") { //2번째 줄부터 사용자 정보
			char tmp_data_str[255] = { 0 };
			(file_data + (z))->available = 1;
			strcpy(tmp_data_str, (!y ? strtok(str_buf, "|") : strtok(0, "|")));
			if (!strcmp(trim(tmp_data_str), " ")) strcpy(tmp_data_str, "(null)");
			
			if (y == 0) strcpy((file_data + z)->id, trim(tmp_data_str));
			if (y == 1) strcpy((file_data + z)->pw, trim(tmp_data_str));
			if (y == 2) strcpy((file_data + z)->name, trim(tmp_data_str));
			if (y == 3) (file_data + z)->level = atof(trim(tmp_data_str));
			if (y == 4) (file_data + z)->score = atoi(trim(tmp_data_str));
			//if (y >= 5) strcpy(file_data[z - 2][y - 2], tmp_data_str);//추가 정보는 addon_data에 저장합니다.
			if (y >= 5 && addon_count > 0) {
				strcpy((file_data + z)->addon_data[y-5], trim(tmp_data_str));
			}
		}
	}

	printf("사용자 %d명, 추가 정보 %d개를 성공적으로 불러왔습니다.\n", user_count, addon_count);
	
	fclose(file_open);

	*user_index_p = user_count;
	*addon_index_p = addon_count;
	*addon_name_p = addon_name;
	return file_data;
}
void data_to_file(user *user_data, int user_count, char **addon_name, int addon_count) {
	printf("정보를 파일에 저장합니다.\n");
	char file_path[255];
	printf("저장할 파일의 경로를 입력해주세요.\n"); gets_s(file_path);
	FILE *file_save = fopen(file_path, "w");
	if (file_save == NULL) { printf("파일을 만들 수 없습니다!\n명령을 취소합니다.\n"); return; }

	printAll(user_data, user_count, addon_name, addon_count, file_save);

	fclose(file_save);
}
void printAll(user *user_data, int user_count, char **addon_name, int addon_count, FILE *outPoint) {
	/*
	IDEA: 어차피 printf도 stdout을 사용하는 거니깐 단순하게 전체 출력을
	출력 방향을 stdout으로 하면 콘솔에 출력할테고,
	출력 방향을 파일 포인터로 하면 파일에 출력될 것입니다.
	*/
	fprintf(outPoint, "       ID | Password |     Name |    Level |         Score");
	if (addon_name != NULL)
		for (int i = 0; i < addon_count; i++) fprintf(outPoint, " | %8s", addon_name[i]);
	fprintf(outPoint, "\n");
	for (int i = 0; i < user_count; i++) if ((user_data + i)->available) {
		user *tmp_ptr = user_data + i;
		fprintf(outPoint, " %8s |", tmp_ptr->id);
		fprintf(outPoint, " %8s |", tmp_ptr->pw);
		fprintf(outPoint, " %8s |", tmp_ptr->name);
		fprintf(outPoint, " %8d |", tmp_ptr->level);
		fprintf(outPoint, " %13.2lf", tmp_ptr->score);
		for (int y = 0; y < addon_count; y++) {
			fprintf(outPoint, " | %8s", tmp_ptr->addon_data[y]);
		}
		fprintf(outPoint, "\n");
	}
}
void print(user user_info) {
	if (user_info.available) {
		printf(" %8s |", user_info.id);
		printf(" %8s |", user_info.pw);
		printf(" %8s |", user_info.name);
		printf(" %8d |", user_info.level);
		printf(" %8.2lf", user_info.score);
		printf("\n");
	}
}
int cmp_score(const void *x, const void *y) {
	if ((*(user*)x).score == (*(user*)y).score) return 0;
	return (((*(user*)x).score >(*(user*)y).score) ? -1 : 1);
}
int cmp_level(const void *x, const void *y) {
	if ((*(user*)x).level == (*(user*)y).level) return 0;
	return (((*(user*)x).level > (*(user*)y).level) ? -1 : 1);
}
void sort(user user_data[], int user_index) {
	int mode = 0;
	while (1) {
		rewind(stdin);
		printf("1) 레벨로 정렬 2) 점수로 정렬\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("잘못 선택하셨습니다.\n");
	}
	if (mode == 1) qsort(user_data, user_index, sizeof(user), cmp_level);
	else qsort(user_data, user_index, sizeof(user), cmp_score);
}
int search_id(user *user_data, int user_count, char *id) {
	for (int i = 0; i < user_count; i++) if (user_data[i].available && !strcmp(id, user_data[i].id)) return i;
	return -1;
}
int search_name(user *user_data, int user_count, char *name) {
	for (int i = 0; i < user_count; i++) if (user_data[i].available && !strcmp(name, user_data[i].name)) return i;
	return -1;
}
void search(user *user_data, int user_count) {
	int mode = 0;
	while (1) {
		rewind(stdin);
		printf("1) ID로 검색 2) 이름으로 검색\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("잘못 선택하셨습니다.\n");
	}
	char keyword[255];
	rewind(stdin);
	printf("검색 키워드를 입력해주세요.\n"); gets_s(keyword);
	int(*cmp_func) (user*, int, char*);
	if (mode == 1) cmp_func = search_id;
	else cmp_func = search_name;

	int result = cmp_func(user_data, user_count, keyword);
	printf("       ID | Password |     Name |    Level |    Score\n");
	if (result >= 0) print(user_data[result]);
	else printf("일치하는 사람이 없습니다!\n");
}
void add_user(user *user_data[], int *user_index_p, int addon_index) {
	user tmp_data;
	printf("사용자를 추가합니다.\n");
	printf("ID를 입력해 주십시오.        "); gets_s(tmp_data.id);
	if (search_id(*user_data, *user_index_p, tmp_data.id) >= 0) {
		printf("이미 존재하는 ID입니다.\n");
		return;
	}
	printf("비밀번호를 입력해 주십시오.  "); gets_s(tmp_data.pw);
	printf("이름을 입력해 주십시오.      "); gets_s(tmp_data.name);
	if (search_name(*user_data, *user_index_p, tmp_data.name) >= 0) {
		printf("이미 존재하는 이름입니다.\n");
		return;
	}
	tmp_data.level = 0;
	tmp_data.score = 0;
	//애드온 데이터 처리
	tmp_data.addon_data = (char**)malloc(sizeof(char*) * addon_index);
	for (int x = 0; x < addon_index; x++) {
		tmp_data.addon_data[x] = (char*)calloc(1, 255 * sizeof(char));
		strcpy(tmp_data.addon_data[x], "(null)");
	}
	tmp_data.available = 1;
	printf("복사할 데이터가 준비되었습니다.\n");
	for (int z = 0; z < *user_index_p; z++) if (!((*user_data)[z].available)) {
		memcpy(&user_data + z, &tmp_data, sizeof(user));
		printf("성공적으로 저장했습니다!\n");
		return;
	}
	printf("빈 공간이 없습니다. 추가로 공간을 만드는 중...\n");

	*user_index_p = (*user_index_p) + 1;
	(*user_data) = (user*)realloc((*user_data), ((*user_index_p) * sizeof(user)));
	memcpy(((*user_data) + ((*user_index_p) - 1)), &tmp_data, sizeof(user));

	if ((*user_data) != NULL) {
		printf("성공적으로 저장했습니다!\n");
	}
	else printf("NULL POINTER ERROR\n");

}
void del_user(user *user_data, int user_index) {
	printf("사용자 삭제 모드\n");
	int mode = 0;
	while (1) {
		rewind(stdin);
		printf("1) ID로 검색 2) 이름으로 검색\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("잘못 선택하셨습니다.\n");
	}
	char keyword[255];
	rewind(stdin);
	printf("검색 키워드를 입력해주세요.\n"); gets_s(keyword);
	int(*cmp_func) (user*, int, char*);
	if (mode == 1) cmp_func = search_id;
	else cmp_func = search_name;

	int result = cmp_func(user_data, user_index, keyword);
	if (result == -1) {
		printf("일치하는 사람이 없습니다!\n");
		return;
	}
	else {
		printf("%s(아이디: %s)님의 계정을 정말로 삭제하시겠습니까?(Y 또는 y)  ", user_data[result].name, user_data[result].id);
		char choice = getchar();
		if (choice == 'y' || choice == 'Y') {
			user_data[result].available = 0;
			printf("%s(아이디: %s)님의 계정을 지웠습니다.\n", user_data[result].name, user_data[result].id);
		}
		else {
			printf("취소되었습니다.\n");
			return;
		}
	}
}
void fix_info(user *user_data, int user_index, char **addon_name, int addon_index) {
	printf("정보 수정을 선택했습니다.\n");
	int mode = 0;
	while (1) {
		rewind(stdin);
		printf("1) ID로 검색 2) 이름으로 검색\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("잘못 선택하셨습니다.\n");
	}
	char keyword[255];
	rewind(stdin);
	printf("검색 키워드를 입력해주세요.\n"); gets_s(keyword);
	int(*cmp_func) (user*, int, char*);
	if (mode == 1) cmp_func = search_id;
	else cmp_func = search_name;

	int result = cmp_func(user_data, user_index, keyword);
	if (result == -1) {
		printf("일치하는 사람이 없습니다!\n");
		return;
	}
	else {
		rewind(stdin);
		char column_name[255] = { 0 };
		char tmp_data[255] = { 0 };
		printf("수정하실 정보열의 이름을 입력해주세요. (ID, PW, NAME, LEVEL, SCORE, 그 외)\n");
		gets_s(column_name);
		rewind(stdin);
		if (!strcmp(column_name, "ID")) {
			printf("수정하실 데이터를 입력해주세요. ");
			gets_s(user_data[result].id);
		}
		else if (!strcmp(column_name, "PW")) {
			printf("수정하실 데이터를 입력해주세요. ");
			gets_s(user_data[result].pw);
		}
		else if (!strcmp(column_name, "NAME")) {
			printf("수정하실 데이터를 입력해주세요. ");
			gets_s(user_data[result].name);
		}
		else if (!strcmp(column_name, "LEVEL")) {
			printf("수정하실 데이터를 입력해주세요. ");
			scanf("%d", user_data[result].level);
		}
		else if (!strcmp(column_name, "SCORE")) {
			printf("수정하실 데이터를 입력해주세요. ");
			scanf("%lf", user_data[result].score);
		}
		else {
			for (int z = 0; z < addon_index; z++) {
				if (!strcmp(column_name, (*addon_name) + z)) {
					printf("%s열의 수정하실 데이터를 입력해주세요.\n", column_name);
					gets_s((user_data[result].addon_data)[z], 255);
					return;
				}
			}
			printf("해당 이름을 가진 자료열이 없습니다.\n");
		}
	}
}
void add_column(user *user_data[], int user_index, char ***addon_name_p, int *addon_index_p) {
	char new_column_name[255] = { 0 };
	printf("콜럼을 추가합니다.\n");
	printf("콜럼의 이름을 입력하시오.  "); gets_s(new_column_name);
	printf("새 콜럼에는 기본값으로 (null) 문자열이 들어갑니다.\n");
	for (int z = 0; z < user_index; z++) {
		(*user_data)[z].addon_data = (char**)realloc((*user_data)[z].addon_data, (*addon_index_p + 1) * 255 * sizeof(char));
		(*user_data)[z].addon_data[2] = (*user_data)[z].addon_data[1] + 255;
		strcpy((*user_data)[z].addon_data[*addon_index_p], "(null)");
	}
	int addon_count = *addon_index_p;
	addon_count++;
	char **addon_name_tmp_1 = *addon_name_p;
	(*addon_name_p) = (char**)realloc(*addon_name_p, addon_count * sizeof(char) * 255);
	(*addon_name_p)[addon_count - 1] = (char *)calloc(1, sizeof(char) * 255 * addon_count);
	strcpy((*addon_name_p)[addon_count - 1], trim(new_column_name));

	for (int i = 0; i < addon_count; i++) printf("{%s}\n", (*addon_name_p)[i]);
	*addon_index_p = addon_count;
}
void exit_prog(void) {
	printf("프로그램을 정말로 종료하시겠습니까?(Y 또는 y)  ");
	char choice = getchar();
	if (choice == 'y' || choice == 'Y') {
		printf("프로그램을 종료합니다.\n");
		exit(0);
	}
	printf("취소되었습니다.\n");
	return;
}
void menu(void) {
	printf("아래 메뉴에서 선택해 주십시오.\n");
	printf("1) 사용자 추가        2) 사용자 삭제\n");
	printf("3) 검색               4) 정보 수정\n");
	printf("5) 전체 출력          6) 정렬 후 전체 출력\n");
	printf("7) 파일에서 읽어오기  8) 파일로 내보내기\n");
	printf("9) 콜럼 추가하기      0) 프로그램 종료하기\n");
}

int main(void) {
	int user_count = 0, addon_count = 0, mode = 0;
	char **addon_name;
	user *user_data = file_to_data(&user_count, &addon_count, &addon_name);
	printAll(user_data, user_count, addon_name, addon_count, stdout);
	while (1) {
		system("cls");
		menu(); scanf("%d", &mode);
		rewind(stdin);
		switch (mode) {
		case 0://프로그램 종료
			exit_prog();
			break;
		case 1://사용자 추가
			add_user(&user_data, &user_count, addon_count);
			break;
		case 2://사용자 삭제
			del_user(user_data, user_count);
			break;
		case 3://검색
			search(user_data, user_count);
			break;
		case 4://수정
			fix_info(user_data, user_count, addon_name, addon_count);
			break;
		case 5://전체 출력
			printAll(user_data, user_count, addon_name, addon_count, stdout);
			break;
		case 6://정렬 후 전체 출력
			sort(user_data, user_count);
			printAll(user_data, user_count, addon_name, addon_count, stdout);
			break;
		case 7://파일에서 읽어오기
			user_data = file_to_data(&user_count, &addon_count, &addon_name);
			break;
		case 8://파일로 내보내기
			data_to_file(user_data, user_count, addon_name, addon_count);
			break;
		case 9://콜럼 추가하기
			add_column(&user_data, user_count, &addon_name, &addon_count);
			break;
		default:
			printf("잘못 입력하셨습니다.\n");
			break;
		}
		rewind(stdin); getchar();
	}
	return 0;
}