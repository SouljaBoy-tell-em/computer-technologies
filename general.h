#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CHECK_ERROR(condition, message_error, error_code) \
            do {                                          \
               if (condition) {                           \
                 	printf ("%s", message_error);           \
                  return error_code;                      \
               }                                          \
            } while(false)

#define MSGSZ 128
#define LEN   100
#define DATABASE "dataBase.txt"


typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;
