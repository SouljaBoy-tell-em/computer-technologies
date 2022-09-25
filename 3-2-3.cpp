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
#define CP "cp"


#define CHECK_ERROR(condition, message_error, error_code) \
            do {                                          \
               if (condition) {                           \
                   printf ("%s", message_error);          \
                   exit (error_code);                     \
               }                                          \
            } while(false)


enum error_code {

    NO_ERROR,
    NOT_MEMORY,
    FILE_AREN_T_OPENING,
};


unsigned long FileSize (FILE * file, struct stat * buf);
size_t copy (char ** argv);
void info (void);
void command_block (int argc, char ** argv, const char * short_option, const struct option * long_option);
void save_specificator (char ** argv);
char * infoSpecificatorFile (FILE * save);


int main (int argc, char ** argv) {

    const char short_option [] = "hv";
    const struct option long_option [] = {
                                           {"help", no_argument, NULL, 'h'},
                                           {"verbose", no_argument, NULL, 'v'},
                                           {NULL, no_argument, NULL, 0}
                                         };

    command_block (argc, argv, short_option, long_option);

    return 0;
}


void command_block (int argc, char ** argv, const char * short_option, const struct option * long_option) {
    
    int long_i = 0, opt = 0, flag_h = 0, flag_v = 0;

    while ((opt = getopt_long (argc, argv, short_option, long_option, &long_i)) != -1) {

        switch (opt) {

            case 'h': flag_h = 1;
                      break;

            case 'v': flag_v = 1;
                      break;

            default : break;
        }
    }

    if (flag_h == 1)
        info ();
    
    if (flag_v == 1) {

        save_specificator (argv);
    }
    
    if (argc >= 3)
        copy (argv);
}


char * infoSpecificatorFile (FILE * save) {
    
    char ch, * save_str = (char * ) malloc (sizeof (char) * LEN);

    while ((ch = getc (save)) != EOF) {
        
        * save_str = ch;
        putchar (* save_str);
        save_str++;    
    }
    * save_str = '\0';
    
    //puts (save_str);
    return save_str;    
}


void save_specificator (char ** argv) {

    FILE * save = fopen ("save.txt", "rb+");
    CHECK_ERROR (save == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    fprintf (save, "%s %s %s", argv[optind], ">", argv[optind + 1]);
    char * mem = (char * ) malloc (sizeof (char) * 10);
    fread (mem, sizeof (char), 100, save);
    fputs (mem, stdout); 
    fclose (save);
}


unsigned long FileSize (FILE * file, struct stat * buf) {

    if (fstat (fileno (file), buf) == 0)
        return buf->st_size;

    return 0;
}


size_t copy (char ** argv) {
    
    struct stat buf = {};
    char rec1 [LEN], rec2 [LEN];
    strcpy (rec1, argv [optind]);
    strcpy (rec2, argv [optind + 1]);

    FILE * file1 = fopen (rec1, "r");
    CHECK_ERROR (file1 == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    FILE * file2 = fopen (rec2, "a");
    CHECK_ERROR (file2 == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    unsigned long size = FileSize (file1, &buf);
    char * mem = (char * ) malloc (size * sizeof (char));
    CHECK_ERROR (mem == NULL, "Problem with opening file.", NOT_MEMORY); 
    fread (mem, sizeof (char), size, file1);
    fwrite (mem, sizeof (char), size, file2);

    return NO_ERROR;
}


void info (void) {
    
    puts ("This program can copy information between 2 files.");
    puts ("If you want copy information between something    ");
    puts ("files, you should point specificator CP in small  ");
    puts ("letters. Struct description: file1 cp file2       ");
}
