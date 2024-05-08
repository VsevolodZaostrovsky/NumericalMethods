#include "2dFourierApprox.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#define c(i, j, n, N) ((n - 1) * N * N + (j - 1) * N + i - 1)