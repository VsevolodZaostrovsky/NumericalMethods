#include "PGaus.h"

#define e(i, j, n) ((i - 1) * (n) + (j - 1))


void synchronize(int total_threads)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
	static int threads_in = 0;
	static int threads_out = 0;

	pthread_mutex_lock(&mutex);

	threads_in++;
	if (threads_in >= total_threads)
	{
		threads_out = 0;
		pthread_cond_broadcast(&condvar_in);
	} else
		while (threads_in < total_threads)
			pthread_cond_wait(&condvar_in,&mutex);

	threads_out++;
	if (threads_out >= total_threads)
	{
		threads_in = 0;
		pthread_cond_broadcast(&condvar_out);
	} else
		while (threads_out < total_threads)
			pthread_cond_wait(&condvar_out,&mutex);

	pthread_mutex_unlock(&mutex);
}

int SolveSystem(int n, double *M, double *b, double *x,
int *memory, int thread_number, int total_threads, int* flag)
{
	double mean;
	double eps = 1e-15;

	for (int j = 0; j < n; j++)
		memory[j] = j;

	if (thread_number == 0)
	{
		mean = 1e-20;
		for (int i = 0; i < n * n; ++i)
		{
			if (M[i] > 0)
				mean += M[i];
			else
				mean -= M[i];
		}
		eps = mean * 1e-10 / (n * n);
	}

	synchronize(total_threads);

	for (int step = 1; step < n + 1; step++)
    { 
		double temp;
        int indMax;
		double max;
		int tmp;
		double v;
		
		if (thread_number == 0)
		{
			indMax = step;
			// ищем главный элемент
			for (int i = step + 1; i < n + 1; ++i)
			{
				if (fabs(M[e(step, indMax, n)]) < fabs(M[e(step, i, n)]))
				{
					indMax = i;
				}
			}
			max = M[e(step, indMax, n)];
			if (fabs(max) < eps) {
				//флаг передаём в структуре
				//ставим флаг всё плохо После синхронайза проверяем флаг				
				flag[0] = 1;
				}

			// меняем столбцы местами, если нужно

			if (indMax != step && flag[0] == 0)
			{
				for (int i = 1; i < n + 1; ++i)
				{
					double temp = M[e(i, step, n)];
					M[e(i, step, n)] = M[e(i, indMax, n)];
					M[e(i, indMax, n)] = temp;
				}
				tmp = memory[indMax - 1];
				memory[indMax - 1] = memory[step - 1];
				memory[step - 1] = tmp;
			}
            
            if(flag[0] == 0) {
			temp = M[e(step, step, n)];

			temp = 1.0/temp;
			for (int j = step; j < n + 1; j++)
				M[e(step, j, n)] *= temp;
			b[step - 1] *= temp;
            }
		}
//		printf("поменяли местаи и отномировали столбцы\n");
//		PrintMatrix(n, M, b, n);

		synchronize(total_threads);
		if(flag[0] == 1) { return -1;}

        //шаг прямого хода метода гаусса
        for (int i = thread_number + step + 1; i < n + 1; i += total_threads)
        {
            v = M[e(i, step, n)];
            for (int j = step; j < n + 1; ++j)
            {
                M[e(i, j, n)] -= v * M[e(step, j, n)];
            }
            b[i - 1] -= v * b[step - 1];
//			printf("\n thread %d: %d done\n", thread_number, i);
        }

		synchronize(total_threads);
//		if(thread_number == 0) { PrintMatrix(n, M, b, n); }
	//		printf("step %d \n", step);
    }
	


    //обратный ход метода гаусса
    if (thread_number == 0) {
		for (int i = n - 1; i >= 0; i--)
		{
			double tmp = b[i];
			for (int j = i + 1; j < n; j++)
				tmp -= M[e(i + 1, j + 1, n)] * x[memory[j]];
			x[memory[i]] = tmp;
		}
/*	for(int i = 0; i < n; ++i) {
		printf("%10.3g ", x[i]);
	} */
	}
    return 0;
}

