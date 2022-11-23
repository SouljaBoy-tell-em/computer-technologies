#include <iostream>
#include <stdio.h>
#include <vector>

using std::vector;

int main() {
 
	int N = 0;
	scanf ("%d", &N);

	vector<double> arr (N);

	double sum = 0;
	int i = 0;
	for (i = 0; i < N; i++) {

		scanf ("%lf", &arr[i]);
		sum += arr[i];
	}

	for (i = 0; i < N; i++) {
		if (arr[i] > sum / N)
			printf ("Student #%d: %lf\n", i + 1, arr[i]);

	return 0;
}