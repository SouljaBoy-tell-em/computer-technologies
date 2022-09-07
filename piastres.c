#include <stdio.h>
#include <math.h>
#include <assert.h>


int main (void) {

    unsigned int n;
    scanf ("%d", &n);
    assert (sum > 0);
    unsigned int arr[n];

    int i = 0, sum = 0;
    for (i; i < n; i++) {

        scanf ("%d", &arr[i]);
        sum += arr[i];

    }

    for (i = 0; i < n; i++)
        printf ("Ship # %d: %s %d\n", i, ((sum / n) > arr[i]) ? "add" : "dele"
        "te", abs (arr[i] - (sum / n)));

}
