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
	printf("���Ϸκ��� ������ �о�ɴϴ�.\n");
	int line_counter = 0;
	int column_index = 0;
	char str_buf[255] = { 0 };

	char fpath[255] = { 0 };
	printf("DB ������ ��θ� �Է��� �ּ���.\n"); gets_s(fpath); rewind(stdin);
	FILE *file_open = fopen(fpath, "r");
	//FILE *file_open = fopen("datafile.txt", "r");
	if (file_open == NULL) { printf("������ �� �� �����ϴ�!\n���α׷��� �����մϴ�.\n"); exit(0); }

	//���� ����
	for (line_counter; !feof(file_open); line_counter++) {
		fgets(str_buf, (int)sizeof(str_buf), file_open);//���� �� �� �б�
		strtok(str_buf, "\n");//�� �� ���� �Ϳ��� �� ������ �ٹٲ��� �����ݴϴ�.

		//ù��° ��
		if (!line_counter) {
			char *tmp_ptr = str_buf;
			while ((tmp_ptr = strpbrk(tmp_ptr, "|")) != NULL) {
				column_index++;
				tmp_ptr++;
			}
			if (column_index < 4) {
				printf("������ ������ �ջ�Ǿ����ϴ�.(NEED_MORE_COLUMN)\n���α׷��� �����մϴ�.\n");
				exit(0);
			}
			continue;
		}
		//�� ���� �ٸ� ��
		int check_addon_data = 0;
		char *tmp_ptr = str_buf;
		//���� �߰��� �����Ͱ� ���ų� �������� �����ڷ� ������
		if (strstr(str_buf, "||") != NULL || str_buf[(strlen(str_buf) - 1)] == '|') {
			printf("������ ������ �ջ�Ǿ����ϴ�.(NULL_COLUMN_DATA)\n���α׷��� �����մϴ�.\n");
			exit(0);
		}
		while ((tmp_ptr = strpbrk(tmp_ptr, "|")) != NULL) {
			check_addon_data++;
			tmp_ptr++;
		}
		if (check_addon_data != column_index) {
			printf("������ ������ �ջ�Ǿ����ϴ�.(DISCORDANCE_BETWEEN_NAME_AND_DATA)\n���α׷��� �����մϴ�.\n");
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

	rewind(file_open);//������ ó������
	//������ �޸𸮿� �ø���
	for (int z = -1; z < user_count; z++) {
		char tmp_data_str[255] = { 0 };
		user *tmp_user_ptr = NULL;
		strcpy(str_buf, "");
		fgets(str_buf, (int)sizeof(str_buf), file_open);
		while ((str_buf[strlen(str_buf) - 1]) == '\n') strtok(str_buf, "\n");
		if (!(strcmp(str_buf, ""))) continue;

		//ù�� �ֵ�� �̸� ��
		if (z == -1) {
			if (addon_count) for (int y = 0; y < addon_count + 5; y++) {
				strcpy(tmp_data_str, (!y ? strtok(str_buf, "|") : strtok(0, "|")));
				if (y > 4) {
					strcpy(addon_name[y - 5], trim(tmp_data_str));
				}
			}
			continue;
		}
		
		for (int y = 0; y < addon_count + 5; y++) if (str_buf != NULL || str_buf != "") { //2��° �ٺ��� ����� ����
			char tmp_data_str[255] = { 0 };
			(file_data + (z))->available = 1;
			strcpy(tmp_data_str, (!y ? strtok(str_buf, "|") : strtok(0, "|")));
			if (!strcmp(trim(tmp_data_str), " ")) strcpy(tmp_data_str, "(null)");
			
			if (y == 0) strcpy((file_data + z)->id, trim(tmp_data_str));
			if (y == 1) strcpy((file_data + z)->pw, trim(tmp_data_str));
			if (y == 2) strcpy((file_data + z)->name, trim(tmp_data_str));
			if (y == 3) (file_data + z)->level = atof(trim(tmp_data_str));
			if (y == 4) (file_data + z)->score = atoi(trim(tmp_data_str));
			//if (y >= 5) strcpy(file_data[z - 2][y - 2], tmp_data_str);//�߰� ������ addon_data�� �����մϴ�.
			if (y >= 5 && addon_count > 0) {
				strcpy((file_data + z)->addon_data[y-5], trim(tmp_data_str));
			}
		}
	}

	printf("����� %d��, �߰� ���� %d���� ���������� �ҷ��Խ��ϴ�.\n", user_count, addon_count);
	
	fclose(file_open);

	*user_index_p = user_count;
	*addon_index_p = addon_count;
	*addon_name_p = addon_name;
	return file_data;
}
void data_to_file(user *user_data, int user_count, char **addon_name, int addon_count) {
	printf("������ ���Ͽ� �����մϴ�.\n");
	char file_path[255];
	printf("������ ������ ��θ� �Է����ּ���.\n"); gets_s(file_path);
	FILE *file_save = fopen(file_path, "w");
	if (file_save == NULL) { printf("������ ���� �� �����ϴ�!\n����� ����մϴ�.\n"); return; }

	printAll(user_data, user_count, addon_name, addon_count, file_save);

	fclose(file_save);
}
void printAll(user *user_data, int user_count, char **addon_name, int addon_count, FILE *outPoint) {
	/*
	IDEA: ������ printf�� stdout�� ����ϴ� �Ŵϱ� �ܼ��ϰ� ��ü �����
	��� ������ stdout���� �ϸ� �ֿܼ� ������װ�,
	��� ������ ���� �����ͷ� �ϸ� ���Ͽ� ��µ� ���Դϴ�.
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
		printf("1) ������ ���� 2) ������ ����\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("�߸� �����ϼ̽��ϴ�.\n");
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
		printf("1) ID�� �˻� 2) �̸����� �˻�\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("�߸� �����ϼ̽��ϴ�.\n");
	}
	char keyword[255];
	rewind(stdin);
	printf("�˻� Ű���带 �Է����ּ���.\n"); gets_s(keyword);
	int(*cmp_func) (user*, int, char*);
	if (mode == 1) cmp_func = search_id;
	else cmp_func = search_name;

	int result = cmp_func(user_data, user_count, keyword);
	printf("       ID | Password |     Name |    Level |    Score\n");
	if (result >= 0) print(user_data[result]);
	else printf("��ġ�ϴ� ����� �����ϴ�!\n");
}
void add_user(user *user_data[], int *user_index_p, int addon_index) {
	user tmp_data;
	printf("����ڸ� �߰��մϴ�.\n");
	printf("ID�� �Է��� �ֽʽÿ�.        "); gets_s(tmp_data.id);
	if (search_id(*user_data, *user_index_p, tmp_data.id) >= 0) {
		printf("�̹� �����ϴ� ID�Դϴ�.\n");
		return;
	}
	printf("��й�ȣ�� �Է��� �ֽʽÿ�.  "); gets_s(tmp_data.pw);
	printf("�̸��� �Է��� �ֽʽÿ�.      "); gets_s(tmp_data.name);
	if (search_name(*user_data, *user_index_p, tmp_data.name) >= 0) {
		printf("�̹� �����ϴ� �̸��Դϴ�.\n");
		return;
	}
	tmp_data.level = 0;
	tmp_data.score = 0;
	//�ֵ�� ������ ó��
	tmp_data.addon_data = (char**)malloc(sizeof(char*) * addon_index);
	for (int x = 0; x < addon_index; x++) {
		tmp_data.addon_data[x] = (char*)calloc(1, 255 * sizeof(char));
		strcpy(tmp_data.addon_data[x], "(null)");
	}
	tmp_data.available = 1;
	printf("������ �����Ͱ� �غ�Ǿ����ϴ�.\n");
	for (int z = 0; z < *user_index_p; z++) if (!((*user_data)[z].available)) {
		memcpy(&user_data + z, &tmp_data, sizeof(user));
		printf("���������� �����߽��ϴ�!\n");
		return;
	}
	printf("�� ������ �����ϴ�. �߰��� ������ ����� ��...\n");

	*user_index_p = (*user_index_p) + 1;
	(*user_data) = (user*)realloc((*user_data), ((*user_index_p) * sizeof(user)));
	memcpy(((*user_data) + ((*user_index_p) - 1)), &tmp_data, sizeof(user));

	if ((*user_data) != NULL) {
		printf("���������� �����߽��ϴ�!\n");
	}
	else printf("NULL POINTER ERROR\n");

}
void del_user(user *user_data, int user_index) {
	printf("����� ���� ���\n");
	int mode = 0;
	while (1) {
		rewind(stdin);
		printf("1) ID�� �˻� 2) �̸����� �˻�\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("�߸� �����ϼ̽��ϴ�.\n");
	}
	char keyword[255];
	rewind(stdin);
	printf("�˻� Ű���带 �Է����ּ���.\n"); gets_s(keyword);
	int(*cmp_func) (user*, int, char*);
	if (mode == 1) cmp_func = search_id;
	else cmp_func = search_name;

	int result = cmp_func(user_data, user_index, keyword);
	if (result == -1) {
		printf("��ġ�ϴ� ����� �����ϴ�!\n");
		return;
	}
	else {
		printf("%s(���̵�: %s)���� ������ ������ �����Ͻðڽ��ϱ�?(Y �Ǵ� y)  ", user_data[result].name, user_data[result].id);
		char choice = getchar();
		if (choice == 'y' || choice == 'Y') {
			user_data[result].available = 0;
			printf("%s(���̵�: %s)���� ������ �������ϴ�.\n", user_data[result].name, user_data[result].id);
		}
		else {
			printf("��ҵǾ����ϴ�.\n");
			return;
		}
	}
}
void fix_info(user *user_data, int user_index, char **addon_name, int addon_index) {
	printf("���� ������ �����߽��ϴ�.\n");
	int mode = 0;
	while (1) {
		rewind(stdin);
		printf("1) ID�� �˻� 2) �̸����� �˻�\n"); scanf("%d", &mode);
		if (mode == 1 || mode == 2) break;
		else printf("�߸� �����ϼ̽��ϴ�.\n");
	}
	char keyword[255];
	rewind(stdin);
	printf("�˻� Ű���带 �Է����ּ���.\n"); gets_s(keyword);
	int(*cmp_func) (user*, int, char*);
	if (mode == 1) cmp_func = search_id;
	else cmp_func = search_name;

	int result = cmp_func(user_data, user_index, keyword);
	if (result == -1) {
		printf("��ġ�ϴ� ����� �����ϴ�!\n");
		return;
	}
	else {
		rewind(stdin);
		char column_name[255] = { 0 };
		char tmp_data[255] = { 0 };
		printf("�����Ͻ� �������� �̸��� �Է����ּ���. (ID, PW, NAME, LEVEL, SCORE, �� ��)\n");
		gets_s(column_name);
		rewind(stdin);
		if (!strcmp(column_name, "ID")) {
			printf("�����Ͻ� �����͸� �Է����ּ���. ");
			gets_s(user_data[result].id);
		}
		else if (!strcmp(column_name, "PW")) {
			printf("�����Ͻ� �����͸� �Է����ּ���. ");
			gets_s(user_data[result].pw);
		}
		else if (!strcmp(column_name, "NAME")) {
			printf("�����Ͻ� �����͸� �Է����ּ���. ");
			gets_s(user_data[result].name);
		}
		else if (!strcmp(column_name, "LEVEL")) {
			printf("�����Ͻ� �����͸� �Է����ּ���. ");
			scanf("%d", user_data[result].level);
		}
		else if (!strcmp(column_name, "SCORE")) {
			printf("�����Ͻ� �����͸� �Է����ּ���. ");
			scanf("%lf", user_data[result].score);
		}
		else {
			for (int z = 0; z < addon_index; z++) {
				if (!strcmp(column_name, (*addon_name) + z)) {
					printf("%s���� �����Ͻ� �����͸� �Է����ּ���.\n", column_name);
					gets_s((user_data[result].addon_data)[z], 255);
					return;
				}
			}
			printf("�ش� �̸��� ���� �ڷ῭�� �����ϴ�.\n");
		}
	}
}
void add_column(user *user_data[], int user_index, char ***addon_name_p, int *addon_index_p) {
	char new_column_name[255] = { 0 };
	printf("�ݷ��� �߰��մϴ�.\n");
	printf("�ݷ��� �̸��� �Է��Ͻÿ�.  "); gets_s(new_column_name);
	printf("�� �ݷ����� �⺻������ (null) ���ڿ��� ���ϴ�.\n");
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
	printf("���α׷��� ������ �����Ͻðڽ��ϱ�?(Y �Ǵ� y)  ");
	char choice = getchar();
	if (choice == 'y' || choice == 'Y') {
		printf("���α׷��� �����մϴ�.\n");
		exit(0);
	}
	printf("��ҵǾ����ϴ�.\n");
	return;
}
void menu(void) {
	printf("�Ʒ� �޴����� ������ �ֽʽÿ�.\n");
	printf("1) ����� �߰�        2) ����� ����\n");
	printf("3) �˻�               4) ���� ����\n");
	printf("5) ��ü ���          6) ���� �� ��ü ���\n");
	printf("7) ���Ͽ��� �о����  8) ���Ϸ� ��������\n");
	printf("9) �ݷ� �߰��ϱ�      0) ���α׷� �����ϱ�\n");
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
		case 0://���α׷� ����
			exit_prog();
			break;
		case 1://����� �߰�
			add_user(&user_data, &user_count, addon_count);
			break;
		case 2://����� ����
			del_user(user_data, user_count);
			break;
		case 3://�˻�
			search(user_data, user_count);
			break;
		case 4://����
			fix_info(user_data, user_count, addon_name, addon_count);
			break;
		case 5://��ü ���
			printAll(user_data, user_count, addon_name, addon_count, stdout);
			break;
		case 6://���� �� ��ü ���
			sort(user_data, user_count);
			printAll(user_data, user_count, addon_name, addon_count, stdout);
			break;
		case 7://���Ͽ��� �о����
			user_data = file_to_data(&user_count, &addon_count, &addon_name);
			break;
		case 8://���Ϸ� ��������
			data_to_file(user_data, user_count, addon_name, addon_count);
			break;
		case 9://�ݷ� �߰��ϱ�
			add_column(&user_data, user_count, &addon_name, &addon_count);
			break;
		default:
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
			break;
		}
		rewind(stdin); getchar();
	}
	return 0;
}