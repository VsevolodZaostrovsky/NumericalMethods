 #include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "ReadPrint.h"
#include "PGaus.h"

typedef struct
{
	int n;
	double *M;
	double *b;
	double *x;
	int *memory;
	int thread_number;
	int total_threads;
	int* flag;
} ARGS;

long int get_full_time(void);

void *TaskForThread(void *parg);

long int get_time(void);

long int get_full_time(void)
{
	struct timeval buf;

	gettimeofday(&buf, 0);

	return buf.tv_sec * 100 + buf.tv_usec/10000;
}

void *TaskForThread(void *parg)
{
	ARGS *arg = (ARGS*)parg;

	SolveSystem(arg->n, arg->M, arg->b, arg->x, arg->memory, arg->thread_number, arg->total_threads, arg->flag);
    
    return NULL;
}

long int get_time(void)
{
	struct rusage buf;

	getrusage(RUSAGE_SELF, &buf);

	return buf.ru_utime.tv_sec * 100 + buf.ru_utime.tv_usec/10000;
}

int main(int nargs, char **args)
{
	int n; //размерность матрицы
	int p; //количество потоков
	int r; //количество выводимых значений
	int s; //номер формулы для инициализации матрицы

	double* M;
	double* b;
	double* x;
	int* memory;
	int* flag;
	pthread_t *threads;
	ARGS *arg;
    
    long int t_full;

	char* filename = NULL;

	if(nargs < 5) {
		printf("4 or 5 args needed \n");
		return -1;
	}

	if(sscanf(args[1], "%d", &n) != 1 || sscanf(args[2], "%d", &p) != 1 ||
        sscanf(args[3], "%d", &r) != 1 || sscanf(args[4], "%d", &s) != 1)
    {
        printf("something wrong with params \n");
		return -1;
    }

	if(s != 1 && s != 2 && s != 3 && s != 4 && s != 0 && s != 5) {
		printf("incorrect s \n");
		return -1;
	}

	if(n <= 0 || p <= 0 || r <= 0) {
		printf("bed parametrs \\n");
		return -1;
	}

	if(s == 0) {
		filename = (char*)malloc(128);
        if(sscanf(args[5], "%s", filename) != 1) {
            free(filename);
            printf("cant open the file \n");
            return -5;
        }
	}

	M = (double*)malloc(n * n * sizeof(double));
	b = (double*)malloc(n * sizeof(double));
	x = (double*)malloc(n * sizeof(double));
	for(int i = 0; i < n; ++i) x[i] = 0;
	memory = (int*)malloc(n * sizeof(int));
	flag = (int*)malloc(1 * sizeof(int)); flag[0] = 0;
	threads = (pthread_t*)malloc(p * sizeof(pthread_t));
	arg = (ARGS*)malloc(p * sizeof(ARGS));

	printf("Programm started\n\n"); 

	ReadMatrix(n, M, b, s, filename);

	printf("Matrix A:\n");
	if(s != 0) FullVector(b, M, n);
	PrintMatrix(n, M, b, r); 

	printf("\nCalculating...\n");

	for (int i = 0; i < p; i++)
	{
		arg[i].n = n;
		arg[i].M = M;
		arg[i].b = b;
		arg[i].x = x;
		arg[i].memory = memory;
		arg[i].thread_number = i;
		arg[i].total_threads = p;
		arg[i].flag = flag;
	}

	t_full = get_full_time();

	for (int i = 0; i < p; ++i)
	{
		if (pthread_create(threads + i, 0, TaskForThread, arg + i))
		{
			fprintf(stderr, "cannot create thread #%d!\n", i);
			if(M) free(M);
            if(b) free(b);
            if(x) free(x);
            if(memory) free(memory);
            if(threads) free(threads);
            if(arg) free(arg);
            if(flag) free(flag);
			return -1;
		}
	}

	for (int i = 0; i < p; ++i)
	{
		if (pthread_join(threads[i], 0))
		{
			fprintf(stderr, "cannot wait thread #%5d!\n", i);
			if(M) free(M);
            if(b) free(b);
            if(x) free(x);
            if(memory) free(memory);
            if(threads) free(threads);
            if(arg) free(arg);
            if(flag) free(flag);
			return -1;
		}
	}

	t_full = get_full_time() - t_full;

	if (flag[0] == 1)
	{
		printf("det = 0 \n");
		if(M) free(M);
        if(b) free(b);
        if(x) free(x);
        if(memory) free(memory);
        if(threads) free(threads);
        if(arg) free(arg);
        if(flag) free(flag);
		return -1;
	}

	printf("\nSolution time = %ld\n", t_full);

	ReadMatrix(n, M, b, s, filename);
    if(s != 0) FullVector(b, M, n);

	printf("\n||Ax - b||^2 = %e\n", TestSolution(n, M, b, x));

	if(s != 0)
		printf("||Ans - b||^2 = %e\n", Accuracy(n, x));
	
	printf("Answer: ");
	PrintVector(n, x, r);
	printf("\n");

	if(M) free(M);
	if(b) free(b);
	if(x) free(x);
	if(memory) free(memory);
	if(threads) free(threads);
	if(arg) free(arg);
	if(flag) free(flag);

	return 0;
}
