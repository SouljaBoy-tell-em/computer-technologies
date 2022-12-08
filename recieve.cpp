#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define MSGSZ     128
#define GET         1



typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


using namespace std;


int main (void) {

    int msqid = 0;
    key_t key = 0;
    message_buf  rbuf;

    cout << "RECIEVE. Input key: ";
    cin >> key;

    if ((msqid = msgget (key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("%s\n", rbuf.mtext);

    int N = 0, val = 0, amountOfBirds = 0;
    sscanf (rbuf.mtext, "%d%n", &N, &val);
    sscanf (rbuf.mtext + val, "%d", &amountOfBirds);

    int birds [amountOfBirds];

    int i = 0;
    for (i = 0; i < amountOfBirds; i++)
        birds [i] = 0;

    for (i = 0; i < amountOfBirds; i++) {

        N--;
        birds[i] = GET;

        if (N == 0) break;
    }

    /*
        -> в функцию и зациклить, лень 
    */
    exit(0);
}