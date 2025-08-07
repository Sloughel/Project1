#include"stu.h"


int main() {
	//FILE* fp;
	//errno_t err = fopen_s(&fp,"sample.cnt","r");
	//if (err != 0) {
	//	printf("fail to open the file\n");
	//	return ERROR;
	//}
	int variable_number = 0, clause_number = 0;
	read_variables_and_clauses(&variable_number, &clause_number);
	int** clause_set = read_in_clauses(clause_number);if (clause_set == NULL)return ERROR;
	int* assignment=NULL;if((assignment=creat_assignment(variable_number,clause_number,clause_set))==NULL)return ERROR;
	clock_t start_time = clock();
	if (dpll(clause_set, clause_number, assignment, variable_number)) {
		printf("该CNF公式可满足，一组解为：\n");
		for (int i = 1; i <= variable_number; i++)
			printf("x%d = %s\n", i, assignment[i] > 0 ? "true" : "false");
	}
	else printf("该CNF公式不可满足\n");
	clock_t end_time = clock();
	double execution_time = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;
	printf("执行时间：%f毫秒\n", execution_time);
	free_clause_set(clause_set,clause_number);
	free(assignment);
}