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

    /*

    int a = atoi (argv[1]);
    int b = atoi (argv[2]);

    if (strcmp (argv[3], "sum") == 0)
        printf ("sum: %d\n", a + b);

    if (strcmp (argv[3], "sub") == 0)
        printf ("sum: %d\n", a - b);

    if (strcmp (argv[3], "mun") == 0)
        printf ("sum: %d\n", a * b);

    if (strcmp (argv[3], "div") == 0)
        printf ("sum: %d\n", a / b);

    else
        puts ("False operation\n");

    */

    /*

    const char short_option [] = "asmd";

    const struct option long_option [] = { {"add", no_argument, NULL, 'a'},
                                           {"sub", no_argument, NULL, 's'},
                                           {"mul", no_argument, NULL, 'm'},
                                           {"div", no_argument, NULL, 'd'},
                                           {NULL, no_argument, NULL, 0}

                                         };

    int long_index = 0, opt = 0, flag_a = 0, flag_s = 0, flag_m = 0, flag_d = 0;

    while ((opt = getopt_long (argc, argv, short_option, long_option, &long_index)) != -1) {

        switch (opt) {

            case 'a': flag_a = 1;
                      break;

            case 's': flag_s = 1;
                      break;

            case 'm': flag_m = 1;
                      break;

            case 'd': flag_d = 1;
                      break;

            default: break;

        }

    }

    if (flag_s == 1)
        printf ("Result: %d\n", atoi (argv[optind + 1]) - atoi (argv[optind]));

    if (flag_m == 1)
        printf ("Result: %d\n", atoi (argv[optind + 1]) * atoi (argv[optind]));

    if (flag_d== 1)
        printf ("Result: %d\n", atoi (argv[optind + 1]) / atoi (argv[optind]));

    */

    /*

    const char short_option [] = "la";

    const struct option long_option [] = { {"ls", no_argument, NULL, 'l'},
                                           {"a", no_argument, NULL, 'a'},
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

    */

    char PathName [PATH_MAX];
    char PN;
    getwd (PathName);

    //if (strcmp (argv[optind + 1], ".") == 0)
      //  exit (EXIT_FAILURE);

    const char short_option [] = "asmd";
      int long_index = 0, opt = 0, flag_a = 0, flag_s = 0, flag_m = 0, flag_d = 0;

    const struct option long_option [] = { {"add", no_argument, NULL, 'a'},
                                           {"sub", no_argument, NULL, 's'},
                                           {"mul", no_argument, NULL, 'm'},
                                           {"div", no_argument, NULL, 'd'},
                                           {NULL, no_argument, NULL, 0}
                                         };

        while ((opt = getopt_long (argc, argv, short_option, long_option, &long_index)) != -1) {

        switch (opt) {

            case 'a': flag_a = 1;
                      break;

            case 's': flag_s = 1;
                      break;

            case 'm': flag_m = 1;
                      break;

            case 'd': flag_d = 1;
                      break;

            default: break;

        }

    }


        DIR * file = opendir (PathName);
        struct dirent * get;

        while (file != NULL) {

            get = readdir (file);

            if (!get)
                break;

            if (strcmp (get->d_name, ".") == 0 || strcmp (get->d_name, "..") == 0 )
                if (flag_a != 1)
                    continue;

            printf ("%s\n", get->d_name);
        }

        closedir (file);
        exit (0);

    //}

    /*

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

    */

    return 0;
}
