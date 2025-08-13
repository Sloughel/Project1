#include"stu.h"


int main() {
	FILE* fp;
	char str[100] = { 0 };
	printf("请输入文件名称：\n");
	scanf_s("%s", str,100);
	errno_t err = fopen_s(&fp,str,"r");
	if (err != 0) {
		printf("fail to open the file\n");
		return ERROR;
	}
	int variable_number = 0, clause_number = 0;
	clock_t start_time = clock();
	read_variables_and_clauses_from_file(&variable_number, &clause_number,fp);
	int** clause_set = read_in_clauses_from_file(clause_number,fp);if (clause_set == NULL)return ERROR;
	clock_t end_time = clock();
	double execution_time = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;
	printf("执行时间：%f毫秒\n", execution_time);
	int* assignment=NULL;if((assignment=creat_assignment(variable_number,clause_number,clause_set))==NULL)return ERROR;
	//int* activity = (int*)calloc(variable_number + 1, sizeof(int));
	//if (activity == NULL) {
	//	printf("fail to allocate memory for activity for activity in main\n");
	//	free(assignment);
	//	free_clause_set(clause_set, clause_number);
	//	free(clause_set);
	//	return ERROR;
	//}
	start_time = clock();
	if (dpll(clause_set, clause_number, assignment, variable_number)) {
		printf("该CNF公式可满足，一组解为：\n");
		for (int i = 1; i <= variable_number; i++)
			printf("x%d = %s\n", i, assignment[i] > 0 ? "true" : "false");
	}
	else printf("该CNF公式不可满足\n");
	end_time = clock();
	execution_time = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;
	printf("执行时间：%f毫秒\n", execution_time);
	free_clause_set(clause_set,clause_number);
	free(assignment);
	fclose(fp);
}