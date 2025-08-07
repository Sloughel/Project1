#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<time.h>
#define ERROR -1
#define MAX_CLAUSE_SIZE 10
int get_num();
void read_variables_and_clauses(int* variable_number, int* clauses_number);
void free_clause_set(int** clause_set, int clause_number);
int** read_in_clauses(int clause_number);
int dpll(int** clause_set, int clause_number, int* assignment, int variable_number);
int* creat_assignment(int variable_number, int clause_number, int** clause_set);
void read_variables_and_clauses_from_file(int* variable_number, int* clause_number, FILE* fp);
int** read_in_clauses_from_file(int clause_number, FILE* fp);