#include"stu.h"
int get_num() {
	char ch; int num = 0; int sign = 1;
	while ((ch = getchar()) < '0' || ch > '9')if (ch == '-') sign = -1;
	while (ch <= '9' && ch >= '0') {
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	ungetc(ch, stdin);
	return num * sign;
}
int get_num_from_file(FILE*fp) {
	char ch; int num = 0; int sign = 1;
	while ((ch = fgetc(fp)) < '0' || ch > '9')if (ch == '-') sign = -1;
	while (ch <= '9' && ch >= '0') {
		num = num * 10 + ch - '0';
		ch = fgetc(fp);
	}
	ungetc(ch, fp);
	return num * sign;
}
int* creat_assignment(int variable_number, int clause_number, int** clause_set) {
	int* assignment = (int*)calloc(variable_number + 1, sizeof(int));
	if (assignment == NULL) {
		printf("fail to allocate memory for assignment int main\n");
		free_clause_set(clause_set, clause_number);
		return NULL;
	}
	return assignment;
}
void free_clause_set(int** clause_set, int clause_number) {
	for (int i = 0; i < clause_number; i++)free(clause_set[i]);
	free(clause_set);
}
void read_variables_and_clauses(int *variable_number,int*clause_number) {
	char ch;
	while ((ch = getchar()) == 'c')while (ch != '\n' && ch != EOF)ch = getchar();//skip the previous parts
	ungetc(ch, stdin);
	if ((ch = getchar()) == 'p')printf("find the 'p'\n");
	*variable_number = get_num(); *clause_number = get_num();
	printf("读取到变量数: %d, 子句数: %d\n", *variable_number, *clause_number);
}
void read_variables_and_clauses_from_file(int* variable_number, int* clause_number,FILE*fp) {
	char ch;
	while ((ch=fgetc(fp)) == 'c')while (ch != '\n' && ch != EOF)ch = fgetc(fp);//skip the previous parts
	ungetc(ch, fp);
	if ((ch = fgetc(fp)) == 'p')printf("find the 'p'\n");
	*variable_number = get_num_from_file(fp); *clause_number = get_num_from_file(fp);
	printf("读取到变量数: %d, 子句数: %d\n", *variable_number, *clause_number);
}
int** read_in_clauses(int clause_number) {
	int** clause_set = (int**)malloc(sizeof(int*) *(size_t) clause_number);
	if (clause_set == NULL) {
		printf("fail to allocate memory for clause_set in main\n");
		return NULL;
	}
	for (int i = 0; i < clause_number; i++) {
		clause_set[i] = (int*)malloc(sizeof(int) * MAX_CLAUSE_SIZE);
		if (clause_set[i] == NULL) {
			printf("fail to allocate memory for clause_set_subarray in main\n");
			free_clause_set(clause_set, clause_number);
			return NULL;
		}
	}
	for (int i = 0; i < clause_number; i++) {
		int temp_num = 0;
		int j = 0;
		while ((temp_num = get_num()) != 0) {
			clause_set[i][j++] = temp_num;
			if (j > MAX_CLAUSE_SIZE) {
				printf("警告: 子句 %d 文字数超过预设最大值\n", i);
				return NULL;
			}
		}
		clause_set[i][j] = 0;
	}
	return clause_set;
}
int** read_in_clauses_from_file(int clause_number,FILE*fp) {
	int** clause_set = (int**)malloc(sizeof(int*) * (size_t)clause_number);
	if (clause_set == NULL) {
		printf("fail to allocate memory for clause_set in main\n");
		return NULL;
	}
	for (int i = 0; i < clause_number; i++) {
		clause_set[i] = (int*)malloc(sizeof(int) * MAX_CLAUSE_SIZE);
		if (clause_set[i] == NULL) {
			printf("fail to allocate memory for clause_set_subarray in main\n");
			free_clause_set(clause_set, clause_number);
			return NULL;
		}
	}
	for (int i = 0; i < clause_number; i++) {
		int temp_num = 0;
		int j = 0;
		while ((temp_num = get_num_from_file(fp)) != 0) {
			clause_set[i][j++] = temp_num;
			if (j >= MAX_CLAUSE_SIZE) {
				printf("警告: 子句 %d 文字数超过预设最大值\n", i);
				return NULL;
			}
		}
		clause_set[i][j] = 0;
	}
	return clause_set;
}