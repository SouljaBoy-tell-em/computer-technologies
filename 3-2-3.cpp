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
#include <errno.h>


#define LEN 50
#define CP "cp"
#define FILE1 "file1.txt"
#define FILE2 "file2.txt"
#define SAVE "save.txt"


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


void command_block (int argc, char ** argv, const char * short_option, const struct option * long_option);
size_t copy ();
void destroyAccessFile ();
unsigned long FileSize (FILE * file);
bool FileStatus (char ** argv);
void info (void);
void outputCommand (void);
void recordDirectory (char ** argv);
void save_specificator (char ** argv);
void clearSave (void);


int main (int argc, char ** argv) {

    const char short_option [] = "hvif";
    const struct option long_option [] = {
                                           {"help", no_argument, NULL, 'h'},
                                           {"verbose", no_argument, NULL, 'v'},
                                           {"interactive", no_argument, NULL, 'i'},
                                           {"force", no_argument, NULL, 'f'},
                                           {NULL, no_argument, NULL, 0}
                                         };
    command_block (argc, argv, short_option, long_option);

    return 0;
}


void command_block (int argc, char ** argv, const char * short_option, const struct option * long_option) {

    fopen (SAVE, "w");
    int long_i = 0, opt = 0, flag_h = 0, flag_v = 0, flag_i = 0, flag_f = 0;
    while ((opt = getopt_long (argc, argv, short_option, long_option, &long_i)) != -1) {

        switch (opt) {

            case 'h': flag_h = 1;
                      break;

            case 'v': flag_v = 1;
                      break;
            
            case 'i': flag_i = 1;
                      break;

            case 'f': flag_f = 1;
                      break;

            default : break;
        }
    }

    if (flag_h == 1)
        info ();

    if (FileStatus (argv) == true) {


        if (flag_i == 1)
            recordDirectory (argv);

        if (flag_v == 1)
            outputCommand ();
    

    //if (flag_f == 1)
      //  destroyAccessFile ();
    
    }

}


void clearSave (void) {

    fopen (SAVE, "w");
}


char context_menu (void) {

    char ch;
    puts ("Do you want record in file ? - y/n");
    ch = getchar ();
    while (getchar () != '\n')
        continue;

    if (strchr ("yn", ch) == 0) {

        puts ("You should take true variant.");
        context_menu ();
    }

    return ch;
}


size_t copy () {

    FILE * file1 = fopen (FILE1, "r");
    CHECK_ERROR (file1 == NULL, "Problem with opening file1.txt", FILE_AREN_T_OPENING);
    FILE * file2 = fopen (FILE2, "w");
    CHECK_ERROR (file2 == NULL, "Problem with opening file2.txt", FILE_AREN_T_OPENING);
    FILE * save = fopen (SAVE, "w");
    CHECK_ERROR (save == NULL, "Problem with opening file save.txt", FILE_AREN_T_OPENING);
    unsigned long size = FileSize (file1);
    char * mem = (char * ) malloc (size * sizeof (char));
    CHECK_ERROR (mem == NULL, "Problem with allocating memory.", NOT_MEMORY); 
    fread (mem, sizeof (char), size, file1);
    fwrite (mem, sizeof (char), size, file2);
    fprintf (save, "%s > %s", FILE1, FILE2);

    fclose (file1);
    fclose (file2);
    fclose (save);

    return NO_ERROR;
}


void destroyAccessFile () {

    clearSave ();
    FILE * file = fopen (FILE2, "w");
    CHECK_ERROR (file == NULL, "Problem with opening file2.txt", FILE_AREN_T_OPENING);
    remove (FILE2);
    fopen (FILE2, "w");   
    copy ();
    fclose (file);    
}


unsigned long FileSize (FILE * file) {
    
    struct stat buf = {};

    if (fstat (fileno (file), &buf) == 0)
        return buf.st_size;

    return 0;
}


bool FileStatus (char ** argv) {

    if (argv [optind] != NULL && argv [optind + 1] != NULL)
        return true;

    return false;
}


void info (void) {
    
    puts ("This program can copy information between 2 files.");
    puts ("If you want copy information between something    ");
    puts ("files, you should point specificator CP in small  ");
    puts ("letters. Struct description: file1 cp file2       ");
    exit (EXIT_SUCCESS);
}


void outputCommand () {

    FILE * save = fopen (SAVE, "r");
    CHECK_ERROR (save == NULL, "Problem with opening file save.txt", FILE_AREN_T_OPENING);
    unsigned long filesize = FileSize (save);
    char * mem = (char * ) calloc (filesize, sizeof (char));
    CHECK_ERROR (mem == NULL, "Problem with allocating memory for MEM.", NOT_MEMORY);
    fread (mem, sizeof (char), filesize, save);
    puts (mem);
    free (mem);
    fclose (save);
}


void recordDirectory (char ** argv) {

    FILE * save = fopen (SAVE, "w");
    DIR * dir = opendir ("."); // dir = opendir (current);
    struct dirent * getDir;
    int amount_of_files = 0, i = 0;

    while ((getDir = readdir (dir)) != NULL) {

        if (strcmp (getDir->d_name, ".") == 0)
            continue;
        amount_of_files++;
    }

    char fileBuffer [amount_of_files][LEN];
    dir = opendir (".");

    while ((getDir = readdir (dir)) != NULL) {

        if (strcmp (getDir->d_name, ".") == 0 || strcmp (getDir->d_name, "..") == 0)
            continue;
        
        strcpy (fileBuffer [i], getDir->d_name);
        i++;
    }

    for (i = 0; i < amount_of_files; i++) {

        if (strcmp (argv [optind + 1], fileBuffer [i]) == 0) {
            
            if (context_menu () == 'n') {

                puts ("NO RECORD FILE1 -> FILE2");
                exit (EXIT_FAILURE);
            }
            
            copy ();
            puts ("file1.txt ->file2.txt");
            exit (EXIT_SUCCESS);      
        }
    }
  
    fclose (save);
}
