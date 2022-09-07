#include <stdio.h>


int nod (int, int);


int main (void) {

    unsigned int a, b;

    while (scanf ("%d %d", &a, &b) == 2 && (a * b) != 0) {
        printf ("result: %d\n", nod (((a >= b) ? a : b), ((a < b) ? a : b)));

    }

    return 0;

}


int nod (int a, int b) {

    if (a % b == 0)
        return b;

    nod (b, a - ((a / b) * b));

}
