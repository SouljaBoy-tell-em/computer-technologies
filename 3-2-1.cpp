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

  const char short_option [] = "asmd";
  const struct option long_option [] =   { {"add", no_argument, NULL, 'a'},
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
  
    return 0;
  
}
