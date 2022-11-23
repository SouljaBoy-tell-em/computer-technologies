#include <iostream>
#include <stdio.h>
#include <vector>

using std::vector;


void reverse (vector<double> & arr, int N);	


int main (void) {

	int N = 0;
	scanf ("%d", &N);

	vector<double> arr (N);

	int i = 0;
	for (i = 0; i < N; i++)
		scanf ("%lf", &arr[i]);

	printf ("BEFORE: ");
	for (i = 0; i < N; i++)
		printf ("%lf ", arr[i]);

	reverse (arr, N);
	printf ("\n\nAFTER: ");
	for (i = 0; i < N; i++)
		printf ("%lf ", arr[i]);

	return 0;
}


void reverse (vector<double> (&arr), int N) {

	int i = 0;
	for (i = 0; i < N / 2; i++) {

		double temp = arr[i];
		arr[i] = arr[N - i - 1];
		arr [N - i - 1] = temp;
	}
}