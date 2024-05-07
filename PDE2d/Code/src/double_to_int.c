#include <stdio.h>
#include <math.h>

int plus(int x, int y){ return x + y; }

int proj(int x) { return plus(x, 5); }


int main(void) {
    double x = 3.5;
    int result = (int)round(x);
    
    printf("Ближайшее целое значение: %d\n", result);
    
    return 0;
}