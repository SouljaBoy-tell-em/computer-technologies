#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>


#define MAXSTRINGLEN 100
#define STRINGOUTPUTLS 512
#define FILESIZE 1000

void FREE (char * mem, char * getNameFile);
unsigned long FileSize (FILE * file);
int enumerationsBuffer (char * buffer, char * currentFile);


int main (void) {

	int p [2];
	char * mem = (char * ) calloc (MAXSTRINGLEN, 	  sizeof (char));
	char * getNameFile =  (char * ) calloc (STRINGOUTPUTLS,  sizeof (char));

	if (pipe (p)) {

		printf ("ERROR!\n");
		exit (EXIT_FAILURE);
	}

	pid_t pid = fork ();

	if (pid == 0) {

		close (p [0]);
		execl ("../ls/a.out", "", NULL); // no arguments;
		dup2 (p[1], 1);	// open descriptor; (вывод в трубу)
		close (p [1]);
	}

	if (pid) {

		close (p [1]);
		read (p [0], mem, STRINGOUTPUTLS);
		FILE * fp = NULL;
		
		while (enumerationsBuffer (mem, getNameFile) && strcmp ("a.out", getNameFile) != 0) {

            if ((fp = fopen (getNameFile, "r"))) {

                struct stat * getName = (struct stat * ) calloc (1, sizeof (struct stat));
                stat (getNameFile, getName);

                if (S_ISREG (getName->st_mode)) {

                    char * buf = (char * ) calloc (FILESIZE, sizeof (char));
                    int file_size = FileSize (fp);
                    fread (buf, sizeof (char), file_size, fp);
                    printf ("%s\n%s\n", getNameFile, buf);
                    fclose (fp);
                    free (buf);   
                }

            }
        }
        close (p[0]);
    }

    FREE (mem, getNameFile);

	return 0;
}


void FREE (char * mem, char * getNameFile) {

	free (mem);
	free (getNameFile);
}


unsigned long FileSize (FILE * file) {

    struct stat buf = {};
    if (fstat (fileno (file), &buf) == 0)
        return buf.st_size;

    return 0;
}


int enumerationsBuffer (char * buffer, char * currentFile) { // buffer - сюда я записываю все файлы, идущие через пробелы;

    static int last = 0;
    int i = 0;

    char currentBuffer [STRINGOUTPUTLS];
    int val = 0;

    sscanf (buffer, "%s%n", currentBuffer, &val);
    i = last = val;
    
    if (buffer [last] == ' ')
        last++;

    int j = 0;
    for (int j = i; j < STRINGOUTPUTLS; j++)
        currentFile [j] = '\0';

    if (last == STRINGOUTPUTLS)
        return 0;

    return 1;
}