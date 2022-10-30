#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>


#define COEFFICIENTITERATION 1024
#define FILE1 "file1.txt"
#define FILE2 "file2.txt"


#define CHECK_ERROR(condition, message_error)			    \
            do {                                          \
               if (condition) {                           \
                   printf ("%s", message_error);          \
               }                                          \
            } while(false)


int amountIteration (int filesize);
bool getDataFromPipe (char * arrayData, int * p, FILE * getStartFile, int filesize);
unsigned long FileSize (FILE * file);
void freePointers (char * mem_start, FILE * getStartFile, FILE * getFinishFile);
void outDataInPipe (char * arrayData, int * p, FILE * getFinishFile, int filesize);


int main () {

	int p [2];

	FILE * getStartFile = fopen (FILE1, "r");
	CHECK_ERROR (getStartFile == NULL, "Problem with opening file1.txt.");
	FILE * getFinishFile = fopen (FILE2, "w");
	CHECK_ERROR (getStartFile == NULL, "Problem with opening file2.txt.");
	int filesize = FileSize (getStartFile);

	char * mem_start = (char * ) calloc (filesize, sizeof (char));
	CHECK_ERROR (mem_start == NULL, "Problem with allocating memory for mem_start.");

	if (pipe (p)) {

		printf ("ERROR!\n");
		exit (EXIT_FAILURE);
	}

	pid_t pid = fork ();
	
	if (pid == 0)
		getDataFromPipe (mem_start, p, getStartFile, filesize);

	if (pid)
		outDataInPipe (mem_start, p, getFinishFile, filesize);

	freePointers (mem_start, getStartFile, getFinishFile);

	return 0;
}


int amountIteration (int filesize) {

	int i = 0, amount_iteration = 0;
	while (filesize != 0) {

		filesize /= COEFFICIENTITERATION;
		amount_iteration++;
	}

	return amount_iteration;
}


bool getDataFromPipe (char * arrayData, int * p, FILE * getStartFile, int filesize) {

	close (p [0]);

	fread (arrayData, sizeof (char), filesize, getStartFile);

	for (int i = 0; i < amountIteration (filesize); i++)
		write (p [1], arrayData, filesize * sizeof (char));

	close (p [1]);

	return true;
}


unsigned long FileSize (FILE * file) {

    struct stat buf = {};
    if (fstat (fileno (file), &buf) == 0)
        return buf.st_size;

    return 0;
}


void freePointers (char * mem_start, FILE * getStartFile, FILE * getFinishFile) {

	free (mem_start);
	fclose (getStartFile);
	fclose (getFinishFile);
}


void outDataInPipe (char * arrayData, int * p, FILE * getFinishFile, int filesize) {

	close (p [1]);

	int i = 0;
	
	for (i = 0; i < amountIteration (filesize); i++) {

		read (p [0], arrayData, filesize * sizeof (int));
		fprintf (getFinishFile, "%s", arrayData);
	}

	close (p [0]);
}