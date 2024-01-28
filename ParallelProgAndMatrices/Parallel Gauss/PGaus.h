#pragma once
#include <pthread.h>
#include <math.h>

int SolveSystem(int n, double *M, double *b, double *x,
int *memory, int thread_number, int total_threads, int* flag);

void synchronize(int total_threads);
