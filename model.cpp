#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



#define CHECK_ERROR(condition, message_error, error_code) \
            do {                                          \
               if (condition) {                           \
                   cout << message_error;   	          \
                   return error_code;                     \
               }                                          \
            } while(false)

#define MSGSZ 128
#define MAXSTRINGINT 10


using namespace std;


typedef struct msgbuf {

	long mtype;
	char * mtext;
} message_buf;


int main (void) {

	int msqid = 0;
	key_t key = 0;

	message_buf send;
	send.mtext = (char * ) malloc (sizeof (char) * MSGSZ);
	char N[MAXSTRINGINT];

	cout << "Input key for msg queue: ";
	cin >> key;
	cout << endl << "Input N and amount of Birds through space: ";
	scanf ("%s", N);


	msqid = msgget (key, IPC_CREAT);
	CHECK_ERROR(key < 0 || msqid == -1, "\nProblem with create queue.", EXIT_FAILURE);

	strcpy (send.mtext, N);
	send.mtype = 1;
	msgsnd (msqid, &send, strlen (send.mtext) + 1, IPC_NOWAIT);

	return 0;
}	