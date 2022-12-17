#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>


#define SIZEBUF 4096
#define SIZENAME 100



int main(int argc, char * argv[]) {

    int fd [2];
    pipe (fd);

    pid_t valueFork = fork ();

    if (valueFork != 0) {

        char str[SIZEBUF], name[SIZENAME];
        int j = 0, i = 0;

        ssize_t len;
        len = read (fd[0], str, SIZEBUF);
        write (1, str, len);

        close (fd[0]);
        close (fd[1]);

        while(str[j] != '\0') {

            if (str[j] != '\n') {

                name[i] = str[j];
                i++;
                j++;
            }

            else {

                printf ("name : \"%s\" \n");

                void * buff = malloc(SIZEBUF);
                FILE * f1 = fopen(name, "r");

                while (fread (buff, sizeof (char), SIZEBUF, f1) != NULL) 
                	printf("%s", (char * ) buff);                
                
                free(buff);
                
                for (i = 0; i < 100; i++) 
                	name[i] = '\0';

                j++;
                i = 0;
            }
        }
    }

    else {

        close (fd[0]);
        dup2 (fd[1], 1);
        execlp ("ls", "ls", NULL);
        close (fd[1]);
    }

    return 0;
}