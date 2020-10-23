#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "TimeType.h"
#include <sys/msg.h>

typedef struct msgbuff
{
        long mtype;
        char mtext[128];
} message_buf;

class MessageHandler
{
public:
        MessageHandler();
        MessageHandler(bool);
        void requestCriticalSection();
        bool grantCriticalSection();
        bool receiveCriticalSection();
        TimeType * checkMessages();
        void sendTimeMessage(TimeType);
        void close();
private:
        void setupMessageQueue();
        bool isChildProc;
        int messageId;
};

#endif /* MESSAGEHANDLER_H */