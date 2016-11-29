#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char *argv[]) {
	char fpath_1[255] = { 0 }, fpath_2[255] = { 0 };
	if (argc < 4) {
		printf("프로그램의 argv로 파일 경로 2개를 입력하셔도 됩니다.\n");
		printf("예시) %s a.txt b.txt\n", argv[0]);
		printf("첫번째 파일의 경로를 입력해 주세요.  "); gets_s(fpath_1); rewind(stdin);
		printf("두번째 파일의 경로를 입력해 주세요.  "); gets_s(fpath_2); rewind(stdin);
	}
	else {
		printf("파일: %s \n", argv[1]); strcpy(fpath_1, argv[1]);
		printf("파일: %s \n", argv[2]); strcpy(fpath_2, argv[2]);
		printf("두 개의 파일을 비교합니다.\n");
	}
	FILE *fp = fopen(fpath_1, "r");
	FILE *fp2 = fopen(fpath_2, "r");
	if (fp == NULL || fp2 == NULL) { printf("파일이 잘못되었습니다.\n"); exit(0); }
	
	for (int lineNum = 1; !feof(fp) || !feof(fp2); lineNum++) {
		char string_1[1023], string_2[1023];
		fgets(string_1, 1020, fp);
		fgets(string_2, 1020, fp2);
		if (strcmp(string_1, string_2)) {
			printf("다른 파일입니다. (%d번째 줄이 다릅니다.)\n", lineNum);
			fclose(fp);
			fclose(fp2);
			exit(0);
		}
	}
	printf("같은 파일입니다.\n");
	fclose(fp);
	fclose(fp2);
	return 0;
}