#include "general.h"


int main (void)
{
    int msqid;
    key_t key;
    message_buf  rbuf;

    scanf ("%d", &key);

    msqid = msgget(key, 0666);
    CHECK_ERROR(msqid < 0, "msqid is bad.\n", EXIT_FAILURE);
    CHECK_ERROR(msgrcv(msqid, &rbuf, MSGSZ, 1, 0) == -1, "msgrcv is bad.\n", EXIT_FAILURE);

    printf("%s\n", rbuf.mtext);

    return 0;
}