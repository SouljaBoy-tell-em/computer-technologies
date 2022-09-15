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


#define LEN 4

int main (int argc, char ** argv) {


    const char short_option [] = "la";

    const struct option long_option [] = { {"ls", no_argument, NULL, 'l'},
                                           {NULL, no_argument, NULL, 0}

                                         };

    int long_index = 0, opt = 0, flag_a = 0, flag_l = 0;

    while ((opt = getopt_long (argc, argv, short_option, long_option, &long_index)) != -1) {

        switch (opt) {

            case 'l': flag_l = 1;
                      break;

            default: break;

        }

    }

    char PathName [PATH_MAX];
    char PN;
    getwd (PathName);

    if (strcmp (argv[optind + 1], ".") == 0)
        exit (EXIT_FAILURE);

    if (flag_l == 1) {

        DIR * file;
        struct dirent * get;
        file = opendir (PathName);

        while (file != NULL) {

            get = readdir (file);
            if (!get)
                break;

            printf ("%s\n", get->d_name);
        
        }

        closedir (file);

    }

    return 0;

}
