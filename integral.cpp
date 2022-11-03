#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <ctime>


#define LIMIT1 0.0
#define LIMIT2 2.0
#define AMOUNTPARTSUMS 4


typedef struct {

	int downlim;
	int uplim;
	int N;
	double sum;
} PartSum;


double askEquation (double x);
void driver (void);
void * flow (void * partSum);


int main (void) {

	driver ();

	//printf ("TIME: %lf\n", (end - start) / (CLOCKS_PER_SEC));
	return 0;
}


double askEquation (double x) {

	return sqrt (4 - x * x);
}


void driver (void) {

	int N = 0, AMOUNTTHREADS = 0;
	scanf ("%d %d", &N, &AMOUNTTHREADS);

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

	double start = clock ();
	for (i = 0; i < AMOUNTTHREADS; i++)
		pthread_create (&threads[i], NULL, flow, &partsum[i]);
	double end = clock ();

	for (i = 0; i < AMOUNTTHREADS; i++)
		pthread_join (threads[i], NULL);

	double sum = 0;
	for (i = 0; i < AMOUNTTHREADS; i++)
		sum += partsum[i].sum;

	printf ("SUM: %lf\n", sum);

}


void * flow (void * partSum) {

	PartSum * partsum = (PartSum * )partSum;

	double part = (LIMIT2 - LIMIT1) / ((PartSum * )partSum)->N, mainFullPart = 0;

	int i = 0;
	for (i = ((PartSum * )partSum)->downlim; i < ((PartSum * )partSum)->uplim; i++)
		mainFullPart += (askEquation (LIMIT1 + i * part) * part);

	((PartSum * )partSum)->sum = mainFullPart;
}