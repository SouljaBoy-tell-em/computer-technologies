/* linoperations.cpp - testing built-in functions. */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <stdlib.h>


#define AREA "########################################"


void use_getgrent (struct group * pts, struct passwd * ptsmain);
void use_getuid ();
void use_getpwuid (struct passwd * pt);
void use_getgid ();
void use_getgrgid (struct group * pts);
char menu ();


int main(){

    struct passwd * pt = getpwuid (getuid ());
    struct group * pts = getgrent ();
    struct group * save = pts;
    struct group * ptz = getgrgid (getgid ());
    struct passwd * ptsmain = getpwuid (getuid());

    char ch;

    while ((ch = menu ()) != '6') {

        switch (ch) {
        
            case '1': use_getuid ();
                      break;
            
            case '2': use_getpwuid (pt);
                      break;

            case '3': use_getgid ();
                      break;

            case '4': use_getgrgid (ptz);
                      break;
            
            case '5': use_getgrent (pts, ptsmain);
                      break;
            
            default:  break;
    
        }

    }
    
    puts ("Program the end.");

    return 0;

}


void use_getgid (void) {
    
    printf ("group ID: %d\n", getgid ());
    
}


void use_getpwuid (struct passwd * pt) {

    printf ("user password: %s\n", pt->pw_passwd);
    printf ("user name: %s\n", pt->pw_name);
    printf ("user ID: %d\n", pt->pw_uid);
    printf ("group ID: %d\n", pt->pw_gid);
    printf ("real name: %s\n", pt->pw_gecos);
    printf ("home directory: %s\n", pt->pw_dir);
    printf ("shell prorgam: %s\n", pt->pw_shell);

}


void use_getuid (void) {

    printf ("user ID: %d\n", getuid());

}


void use_getgrent (struct group * pts, struct passwd * ptsmain) {

    printf ("REAL NAME: %s\n\n", ptsmain->pw_gecos);
    printf ("group name: %s\n", pts->gr_name);
    printf ("group password: %s\n", pts->gr_passwd);
    printf ("group ID: %d\n", pts->gr_gid);

    int i = 1;

    while (pts != NULL) {
        
        if ( * (pts->gr_mem) != NULL && strcmp (ptsmain->pw_gecos, * (pts->gr_mem)) == 0)
            printf ("group %d: %s\n", i, * (pts->gr_mem));

        i++;
        pts = getgrent ();
    }

    puts ("Program the end.");
    exit (0);

}


void use_getgrgid (struct group * pts) {

    printf ("group name: %s\n", pts->gr_name);
    printf ("password of group: %s\n", pts->gr_passwd);
    printf ("identification of group: %d\n", pts->gr_gid);
    printf ("group %s", * (pts->gr_mem));

    while ( * (pts->gr_mem) != NULL) {

        printf ("group %s", *(pts->gr_mem));
        ( * (pts->gr_mem))++;
    }

}


char menu (void) {

    char ch;

    puts (AREA);
    puts ("1) getuid;                    2) getpwuid;");
    puts ("3) getgid                     4) getgrgid;");
    puts ("5) getgrent                   6) QUIT     ");
    putchar ('\n');
    puts ("getgrent is one-use func.");
    puts (AREA);
    putchar ('\n');

    ch = getchar ();
    while (getchar () != '\n')
        continue;
    
    return ch;

}
