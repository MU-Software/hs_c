#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(void) {
	char fpath_1[255] = { 0 }, fpath_2[255] = { 0 };
	printf("첫번째 파일의 경로를 입력해 주세요.  "); gets_s(fpath_1); rewind(stdin);
	printf("두번째 파일의 경로를 입력해 주세요.  "); gets_s(fpath_2); rewind(stdin);
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