#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <getopt.h>


#define a 0
#define b 1
#define l 1.0
#define c 1
#define RESTIME 0.3


typedef struct {

	int thread;
	int amount;
	int downlimOld;
	int uplimOld;
	int downlimNew;
	int uplimNew;
	double * old_data;
	double * new_data;
	int index;
	double T;
	double t;
	int M;
} Group;


void * func (void * val) {

	int j = 0;
	while (((Group * )val)->downlimNew < (int ) ((((Group * )val)->T) / (((Group * )val)->t))) {

		for (j = ((Group * )val)->uplimOld; j > 1; j--) {

			((Group * )val)->new_data[j] = ((Group * )val)->old_data[j] + 
			RESTIME * (((Group * )val)->old_data[j + 1] - 2 * ((Group * )val)->old_data [j] + 
			((Group * )val)->old_data[j - 1]);
			((Group * )val)->amount++;
			if ((((Group * )val)->amount) == (((Group * )val)->downlimNew + 1) * (int) (((int ) ((((Group * )val)->T) / (((Group * )val)->t))) / ((Group * )val)->thread)) {

				((Group * )val)->amount++;
				return NULL;
			}
		}

		((Group * )val)->old_data = ((Group * )val)->new_data;
		((Group * )val)->downlimNew++;
		((Group * )val)->uplimOld = ((Group * )val)->M - 2;
	}

	FILE * rec = fopen ("rec.txt", "w");
	int i = 0;
	for (i = 0; i < (int ) ((((Group * )val)->T) / (((Group * )val)->t)); i++) {

		fprintf (rec, "%lf ", ((Group * )val)->old_data[i]);

		if (((Group * )val)->old_data[i] == c)
			break;
	}
}


int main (int argc, char ** argv) {

	int M = atoi (argv [optind]);
	int T = atof (argv [optind + 1]);
	int P = atoi (argv [optind + 2]);
	double h = l / M, t = (RESTIME * h * h);

	Group group = {};
	group.old_data = (double * ) calloc (M, sizeof (double));
	group.new_data = (double * ) calloc (M, sizeof (double));
	group.index = 0;
	group.T = T;
	group.t = t;
	group.M = M;
	group.amount = 0;
	group.uplimOld = M - 2;
	group.downlimNew = 0;
	group.thread = P;

	int i = 0;
	for (i = 0; i < M; i++) {

		group.old_data [i] = 0;
		group.new_data [i] = 0;
	}
	group.new_data[M - 1] = 1;
	group.old_data[M - 1] = 1;

	pthread_t thread [P];

	for (i = 0; i < P; i++)
		pthread_create (&thread[i], NULL, func, &group);

	for (i = 0; i < P; i++)
		pthread_join (thread[i], NULL);


	
	return 0;
}