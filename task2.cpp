#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;



typedef struct cont {

	char * name;
	int * sides;
	int volume;
} Cont;



int comp (const void * i, const void * j);
int comp1 (const void * i, const void * j);
int comp2 (const void * i, const void * j);


int main (void) {

	int N = 0, i = 0;
	scanf ("%d", &N);

	Cont conts[N];
	for (i = 0; i < N; i++) {

		conts[i].name = (char * ) calloc (21, sizeof (char));
		conts[i].sides = (int * ) calloc (3,  sizeof (int ));
		scanf ("%s", conts[i].name);
		scanf ("%d", &conts[i].sides[0]);
		scanf ("%d", &conts[i].sides[1]);
		scanf ("%d", &conts[i].sides[2]);
		qsort (conts[i].sides, 3, sizeof (int), comp);
	}

	
	int maxBoxesSize [(N + 1) / 2];

	for (i = 0; i < (N + 1) / 2; i++) {

		maxBoxesSize[i] = con
	}

	return 0;
}


int comp (const void * i, const void * j) {

	return ( * (int * ) i) - ( * (int * ) j);
}