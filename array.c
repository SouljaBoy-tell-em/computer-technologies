#include <stdio.h>
#include <string.h>

int * foo (int * arr, int size);


int main (void) {

    int n, i;
    scanf ("%d", &n);
    int arr[n];

    for (i = 0; i < n; i++)
        scanf ("%d", &arr[i]);

    foo (arr, n);

    for (i = 0; i < n; i++)
        printf ("%d ", arr[i]);

    return 0;

}


int * foo (int * arr, int size) {

    int i = 0;
    for (i = 0; i < size; i++) {

        if (* (arr + i) % 2 == 0)
            (* (arr + i)) *= 2;

        else
            (* (arr + i)) += 2;

    }

    return arr;

}
