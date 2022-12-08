#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSZ     128



typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


int main (void)
{
    int msqid;
    key_t key;
    message_buf  rbuf;

    scanf ("%d", &key);

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("%s\n", rbuf.mtext);
    exit(0);
}