#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <ctime>


#define AMOUNTPARTSUMS 4
#define LIMIT1 0.0
#define LIMIT2 2.0
#define AMOUNTTESTS 10


typedef struct {

	int downlim;
	int uplim;
	int N;
	double sum;
} PartSum;


double askEquation (double x);
void driver (int N, int AMOUNTTHREADS);
void * flow (void * partSum);


int main (void) {

	int i = 0, N = 0, AMOUNTTHREADS = 0;
	scanf ("%d %d", &N, &AMOUNTTHREADS);

	double start = clock ();
	for (i = 0; i < AMOUNTTESTS; i++)
		driver (N, AMOUNTTHREADS);
	double end = clock ();

	printf ("AVG TIME: %lf\n", (end - start) / (CLOCKS_PER_SEC * AMOUNTTHREADS));
	return 0;
}


double askEquation (double x) {

	return sqrt (4 - x * x);
}


void driver (int N, int AMOUNTTHREADS) {

	const int increase = N / AMOUNTTHREADS;
	pthread_t threads [AMOUNTTHREADS];
	PartSum partsum [AMOUNTTHREADS];

	partsum[0].downlim = 0;
	partsum[0].uplim = increase;
	partsum[0].N = N;
	int i = 0;
	for (i = 1; i < AMOUNTTHREADS; i++) {
		partsum[i].N = N;
		partsum[i].downlim = partsum[i - 1].uplim;
		partsum[i].uplim = (partsum[i].downlim + increase);
	}

	for (i = 0; i < AMOUNTTHREADS; i++)
		pthread_create (&threads[i], NULL, flow, &partsum[i]);

	for (i = 0; i < AMOUNTTHREADS; i++)
		pthread_join (threads[i], NULL);

	double sum = 0;
	for (i = 0; i < AMOUNTTHREADS; i++)
		sum += partsum[i].sum;

	printf ("SUM: %lf\n", sum);

}


void * flow (void * partSum) {

	double part = (LIMIT2 - LIMIT1) / ((PartSum * )partSum)->N, mainFullPart = 0;

	int i = 0;
	for (i = ((PartSum * )partSum)->downlim; i < ((PartSum * )partSum)->uplim; i++)
		mainFullPart += (askEquation (LIMIT1 + i * part) * part);

	((PartSum * )partSum)->sum = mainFullPart;
}
