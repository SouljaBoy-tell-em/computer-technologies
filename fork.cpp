#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


#define LENARRAY 5


#define CHECK_ERROR(condition, message_error)			  \
            do {                                          \
               if (condition) {                           \
                   printf ("%s", message_error);          \
               }                                          \
            } while(false)


bool getDataFromPipe (int * arrayData, int * p);
int outDataInPipe (int * arrayData, int * p);


int main () {

	int p [2];
	int * arrayData = (int * ) calloc (LENARRAY, sizeof (int));

	if (pipe (p)) {

		printf ("ERROR!\n");
		exit (EXIT_FAILURE);
	}

	pid_t pid = fork ();
	
	if (pid == 0)
		CHECK_ERROR (getDataFromPipe (arrayData, p) == false, "Inputing uncorrect data.\n");

	if (pid)
		printf ("sum is %d\n", outDataInPipe (arrayData, p));

	free (arrayData);

	return 0;
}


bool getDataFromPipe (int * arrayData, int * p) {

	close (p [0]);

	int i = 0;
	for (i = 0; i < LENARRAY; i++) 
		if (!scanf ("%d", &arrayData [i]))
			return false;

	for (i = 0; i < LENARRAY; i++)
		write (p [1], &arrayData [i], sizeof (int));

	close (p [1]);

	return true;
}


int outDataInPipe (int * arrayData, int * p) {

	close (p [1]);
	read (p [0], arrayData, LENARRAY * sizeof (int));
	
	int i = 0, sum = 0;
	for (i = 0; i < LENARRAY; i++)
		sum += arrayData [i];

	close (p [0]);

	return sum;
}