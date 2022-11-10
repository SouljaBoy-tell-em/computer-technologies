#include <stdio.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv)
{
    double start = clock();

    double sum = 0;
    int N = atoi(argv[1]);
    double d = (double) 2 / (double) N;

    int i = 0;
    for (i = 0; i < N - 1; i++)
        sum += sqrt(4 - i * d * i * d) * d; 

    double finish = clock ();

    printf ("sum = %f\n", sum);
    printf ("TIME: %lf\n", (finish - start) / CLOCKS_PER_SEC);

    return 0;
}