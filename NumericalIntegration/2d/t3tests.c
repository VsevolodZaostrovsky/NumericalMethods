#include "Solution.h"




int main(int argc, char *argv[])
{
    int N = 100;
    double Lx, Ly;
    FILE *fp;

    if (argc < 5)
    {
        printf("Wrong number of parameters, must be 4 in format:\n");
        printf("Lx Ly N filename \n");
        return -1;
    }

    Lx = atof(argv[1]);
    Ly = atof(argv[2]);
    N = atoi(argv[3]);

    if ((fp = fopen(argv[4], "w")) == NULL) // имя файла, в который нужно записать ответ
    {
        printf("Не удалось открыть файл");
        return 0;
    }

    WriteTriangulation(N, Lx, Ly, fp);
    fclose(fp);
    return 0;
}
