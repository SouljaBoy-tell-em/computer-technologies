#include "general.h"


int main (void) {

	int msqid;
	key_t key  = 0;
	size_t len = 0;
	message_buf send = {};
	char message[LEN];

	printf ("Input key:\n");
	scanf ("%d", &key);

	msqid = msgget (key, IPC_CREAT | 0666);
	CHECK_ERROR (msqid == -1, "msqid is bad.\n", EXIT_FAILURE);
	send.mtype = 1;

	printf ("\nInput message: ");
	scanf ("%s", message);

	(void) strcpy (send.mtext, message);
	msgsnd (msqid, &send, strlen (send.mtext) + 1, IPC_NOWAIT);
	CHECK_ERROR (msqid == -1, "msgsnd is bad.\n", EXIT_FAILURE);

	printf("Message: \"%s\" Sent\n", send.mtext);

	return 0;
}	