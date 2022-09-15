#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>



int main(){

    /*

    printf ("user ID: %d\n", getuid());

    */

    /*

    struct passwd * pt = getpwuid (getuid ());

    printf ("user password: %s\n", pt->pw_passwd);
    printf ("user name: %s\n", pt->pw_name);
    printf ("user ID: %d\n", pt->pw_uid);
    printf ("group ID: %d\n", pt->pw_gid);
    printf ("real name: %s\n", pt->pw_gecos);
    printf ("home directory: %s\n", pt->pw_dir);
    printf ("shell prorgam: %s\n", pt->pw_shell);

    */

    /*

    printf ("group ID: %d\n", getgid ());

    */

    /*
    
    struct group * pts = getgrgid (getgid ());

    printf ("group name: %s\n", pts->gr_name);
    printf ("password of group: %s\n", pts->gr_passwd);
    printf ("identification of group: %d\n", pts->gr_gid);
    printf ("group %s", *(pts->gr_mem));

    while ( * (pts->gr_mem) != NULL) {

        printf ("group %s", *(pts->gr_mem));
        (* (pts->gr_mem))++;
    }

    */

    struct group * pts = getgrent ();
    
    printf ("group name: %s\n", pts->gr_name);
    printf ("group password: %s\n", pts->gr_passwd);
    printf ("group ID: %d\n", pts->gr_gid);

    int i = 1;
    while (*(pts->gr_mem) != NULL) {
    
        printf ("group %d: %s\n", i, *(pts->gr_mem));
        i++;
        pts = getgrent();
    }



    return 0;
}
