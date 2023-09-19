#pragma once

// Решает СЛУ, представленную матрицей double *M и вектором значений double *b. Ответ записывается в double *x. Требует N доп памяти - int *memory
int solve(int n, double *M, double *b, double *x, int *memory);