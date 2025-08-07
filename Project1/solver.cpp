#include"stu.h"

int** copy_clause_set(int** clause_set, int clause_number) {
    int** new_set = (int**)malloc(sizeof(int*) * (size_t)clause_number);
    if (!new_set) return NULL;
    for (int i = 0; i < clause_number; i++) {
        new_set[i] = (int*)malloc(sizeof(int) * MAX_CLAUSE_SIZE);
        if (!new_set[i]) {
            for (int j = 0; j < i; j++) free(new_set[j]);
            free(new_set);
            return NULL;
        }
        memcpy(new_set[i], clause_set[i], sizeof(int) * MAX_CLAUSE_SIZE);
    }
    return new_set;
}
int apply_unit_clause(int** clause_set, int clause_number, int* assignment, int variable_number) {
    int has_unit_clause = 1;
    while (has_unit_clause) {
        /////////
        int last_unit_variable = -1;
        has_unit_clause = 0;int count = 0;
        for (int i = 0; i < clause_number; i++) {
            count = 0;
            for (int j = 0; clause_set[i][j] != 0; j++) {
                int lit = abs(clause_set[i][j]);
                if (assignment[lit] == 0) {
                    count++;
                    last_unit_variable = clause_set[i][j];//��¼��Ԫ��
                }
                if (count > 1)break;
            }
            ////////
            if (count == 1) {
                has_unit_clause = 1;
                int lit = abs(last_unit_variable);
                assignment[lit] = last_unit_variable;//���Ӿ�Ԫ�أ���ֵΪ����
                for (int a = 0; a < clause_number; a++) {
                    for (int j = 0; clause_set[a][j] != 0; j++) {
                        if (clause_set[a][j] == last_unit_variable) {
                            clause_set[a][0] = 0;//ӵ����ͬԪ�أ����Ϊ����
                            break;
                        }
                        else if (clause_set[a][j] == -last_unit_variable) {
                            int k;
                            for ( k = j; clause_set[a][k] != 0; k++)clause_set[a][k] = clause_set[a][k + 1];//��Ԫ���ڴ˴������㣬ֱ��ɾ��
                            clause_set[a][k] = 0;//��֤ĩβΪ0
                            if (clause_set[a][0] == 0)return 0;//ĳ���Ӿ䱻ɾ����ȫ����ʾ���������㣬retrun 0 ��ʾ������
                            --j;
                        }
                    }
                }
                /////
                printf("���Ӿ�Ԫ��Ϊ%d\n", last_unit_variable);
                for (int i = 0; i < clause_number; i++) {
                    printf("��%d�Ӿ�Ϊ: ", i);
                    for (int j = 0; clause_set[i][j] != 0; j++) {
                        printf("%d ", clause_set[i][j]);
                    }
                    printf("\n");
                }
                //////
            }
           
            ////////������Ѱ�ҵ����Ӿ��has_unit_clause����ֵΪ1����ʾ�ظ�һ�ε��Ӿ�ԭ��
        }
        ////
    }
    return 1;//return 1 ��ʾ��ɵ��Ӿ�ԭ��
}
int all_clauses_satisfied(int** clause_set, int clause_number, int* assignment) {
    for (int i = 0; i < clause_number; i++) {
        if (clause_set[i][0] == 0)continue;
        int satisfied = 0;
        for (int j = 0; clause_set[i][j] != 0; j++) {
            int lit = clause_set[i][j];
            int var = abs(lit);
            if (assignment[var] == lit) {
                satisfied = 1;
                break;
            }
        }
        if (!satisfied) return 0;
    }
    return 1;
}
int select_variable(int** clause_set, int clause_number, int* assignment, int variable_number) {
    // �򵥲��ԣ�ѡ���һ��������δ��ֵ����
    for (int i = 0; i < clause_number; i++) {
        for (int j = 0; clause_set[i][j] != 0; j++) {
            int var = abs(clause_set[i][j]);
            if (assignment[var] == 0)return var;
        }
    }
    return 0; // ���б������Ѹ�ֵ
}
int dpll(int** clause_set, int clause_number, int* assignment, int variable_number) {
    int** new_clause_set = (int**)copy_clause_set(clause_set, clause_number);
    if (new_clause_set == NULL) {
        printf("fail to allocate memory for new_clause_set in dpll");
        return ERROR;
    }
    int* new_assignment = (int*)malloc(sizeof(int) *(size_t)(variable_number + 1));
    if (!new_assignment) {
        free_clause_set(new_clause_set,clause_number);
        printf("fail to allocate memory for new_assignment in dpll\n");
        return ERROR;
    }
    memcpy(new_assignment, assignment, sizeof(int) *(size_t)(variable_number + 1));
    if(apply_unit_clause(new_clause_set, clause_number, new_assignment, variable_number)==0)return 0;
    int var = select_variable(new_clause_set, clause_number, new_assignment, variable_number);
    if (var == 0) {
        // ���б������Ѹ�ֵ
        if (all_clauses_satisfied(new_clause_set, clause_number, new_assignment)) {
            memcpy(assignment, new_assignment, sizeof(int) * (size_t)(variable_number + 1));
            free_clause_set(new_clause_set, clause_number);
            free(new_assignment);
            return 1;
        }
        free_clause_set(new_clause_set, clause_number);
        free(new_assignment);
        return 0;
    }
    // ���Ը�ֵΪ��
    new_assignment[var] = var;
    printf("���Ը�ֵ%d\n", var);
    if (dpll(new_clause_set, clause_number, new_assignment, variable_number)) {
        memcpy(assignment, new_assignment, sizeof(int) * (variable_number + 1));
        free_clause_set(new_clause_set, clause_number);
        free(new_assignment);
        return 1;
    }
    // ���Ը�ֵΪ��
    new_assignment[var] = -var;
    printf("���Ը�ֵ%d\n", -var);
    if (dpll(new_clause_set, clause_number, new_assignment, variable_number)) {
        memcpy(assignment, new_assignment, sizeof(int) * (variable_number + 1));
        free_clause_set(new_clause_set, clause_number);
        free(new_assignment);
        return 1;
    }
    // ���ָ�ֵ��ʧ��
    free_clause_set(new_clause_set, clause_number);
    free(new_assignment);
    printf("����%d\n",abs(var));
    return 0;
}

//int select_variables_with_VSIDS() {
//
//}