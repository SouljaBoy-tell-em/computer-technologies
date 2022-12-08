#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


#define CHECK_ERROR(condition, message_error, error_code) \
            do {                                          \
               if (condition) {                           \
                   cout << message_error;   	          	 \
                   return error_code;                     \
               }                                          \
            } while(false)

#define MSGSZ 128
#define LEN   100
#define DATABASE "dataBase.txt"


using namespace std;


typedef struct msgbuf {

	long mtype;
	char mtext[MSGSZ];
} message_buf;


int main (void) {

	int msqid;
	key_t key  = 0;
	size_t len = 0;
	message_buf send = {};
	char message[LEN];

	printf ("Input key:\n");
	scanf ("%d", &key);

	msqid = msgget (key, IPC_CREAT | 0666);
	send.mtype = 1;

	printf ("\nInput message: ");
	scanf ("%s", message);

	(void) strcpy (send.mtext, message);
	msgsnd (msqid, &send, strlen (send.mtext) + 1, IPC_NOWAIT);

	printf("Message: \"%s\" Sent\n", send.mtext);

	return 0;
}	