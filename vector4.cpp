#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using std::vector;


int explore (vector<double> (&arr), int N, double compareNumber);


int main (void) {

	int N = 0;
	double compareNumber = 0;

	printf ("Compare number: \n");
	scanf ("%lf", &compareNumber);
	printf ("Amount element of array: \n");
	scanf ("%d", &N);

	vector<double> arr (N);

	int i = 0;
	for (i = 0; i < N; i++)
		scanf ("%lf", &arr[i]);

	int indexMin = explore (arr, N, compareNumber);

	if (indexMin < 0)
		printf ("So element not found.\n");

	else
		printf ("Index element is %d\n", indexMin + 1);

	return 0;
}


int explore (vector<double> (&arr), int N, double compareNumber) {

	double min = 1000000;
	int indexMin = -1;

	int i = 0;
	for (i = 0; i < N; i++) {

		if (arr[i] > compareNumber) {

			if (arr[i] < min) {

				min = arr[i];
				indexMin = i;
			}
		}
	}

	return indexMin;
}