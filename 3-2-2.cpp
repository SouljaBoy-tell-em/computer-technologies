#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <limits.h>
#include <string.h>


#define LEN 50


void delim (char * current, char * rootCurrent);


int main (int argc, char ** argv) {

    const char short_option [] = "alR";
    const struct option long_option [] = {
                                           {"all", no_argument, NULL, 'a'},
                                           {"long", no_argument, NULL, 'l'},
                                           {"recursive", no_argument, NULL, 'R'},
                                           {NULL, no_argument, NULL, 0}
                                         };

    int long_i = 0, opt = 0, flag_a = 0, flag_l = 0, flag_R = 0;

    while ((opt = getopt_long (argc, argv, short_option, long_option, &long_i)) != -1) {

        switch (opt) {

            case 'a': flag_a = 1;
                      break;

            case 'l': flag_l = 1;
                      break;

            case 'R': flag_R = 1;
                      break;

            default : break;

        }

    }

    char * current = get_current_dir_name ();
    char rootCurrent [LEN];
    delim (current, rootCurrent);

    DIR * dir = opendir ("."); // dir = opendir (current);

    if (argc >= 2 && strcmp (argv[1], "..") == 0)
        dir = opendir (".."); // dir = opendir (rootCurrent);

    struct dirent * getDir;
    while ((getDir = readdir (dir)) != NULL) {

        if (flag_a != 1)
            if (strcmp (getDir->d_name, ".") == 0 || strcmp (getDir->d_name, "..") == 0)
                continue;

        printf ("%s\n", getDir->d_name);
    }

    return 0;
}

void delim (char * current, char * rootCurrent) {

    int i = 0, Delim = 0, flagDelim = 0;

    for (i = 0; i < strlen (current); i++)
        if ( * (current + i) == '/')
            Delim++;

    for (i = 0; i < strlen (current); i++) {

        if ( * (current + i) == '/')
            flagDelim++;

        if (flagDelim == Delim) {

            * (rootCurrent + i) = '\0';
            break;

        }

        * (rootCurrent + i) = * (current + i);

    }

}

