//Import Statements
#include <iostream>
#include <unistd.h>
#include <sys/msg.h>
#include <string>
#include <cstring>
#include "TimeType.h"
#include "MessageHandler.h"
#include "Exception.h"

//Namespace acting weird, just won't use it. Will create functions differently.

MessageHandler::MessageHandler()
{
    isChildProc = false;

    setupMessageQueue();
}

MessageHandler::MessageHandler(bool childProc)
{
    isChildProc = childProc;

    setupMessageQueue();
}

void MessageHandler::setupMessageQueue()
{
    key_t key;

    if ((key = ftok(".", 1)) == (key_t) -1)
    {
        throw Exception("There was an error setting the message queue key: " + std::to_string(errno));
    }

    messageId = msgget(key, 0777 | IPC_CREAT);

    if(messageId < 0)
    {
        throw Exception("There was an error getting the message queue.");
    }
}

void MessageHandler::requestCriticalSection()
{
    if(!isChildProc)
    {
        throw Exception("Only the child process can request the critical section.");
    }

    message_buf message;
    size_t messageLength;
    int pid = getpid();

    message.mtype = 1;
    strcpy(message.mtext, std::to_string(pid).c_str());
    messageLength = strlen(message.mtext) + 1;

    if (msgsnd(messageId, &message, messageLength, 0) < 0)
    {
        throw Exception("There was an error sending the message requesting the critical section.");
    }
}

bool MessageHandler::grantCriticalSection()
{
    if(isChildProc)
    {
        throw Exception("Only the oss process can grant the critical section.");
    }

    message_buf message;

    if(msgrcv(messageId, &message, 128, 1, IPC_NOWAIT) < 0) 
    {
        if(errno == ENOMSG)
        {
            return false;
        }

        else
        {
            throw Exception("There was an error receiving the message.");
        }
    }

    else
    {
        message_buf new_msg;
        size_t messageLength;

        new_msg.mtype = 2;
        strcpy(new_msg.mtext, message.mtext);
        messageLength = strlen(new_msg.mtext) + 1;

        if(msgsnd(messageId, &new_msg, messageLength, IPC_NOWAIT) < 0)
        {
            throw Exception("There was an error sending the message granting critical section access.");
        }

        return true;
    }
}

bool MessageHandler::receiveCriticalSection()
{
        if(!isChildProc)
        {
            throw Exception("Only the child process can request the critical section.");
        }

        message_buf message;

        if(msgrcv(messageId, &message, 128, 2, 0) < 0)
        {
                throw Exception("There was an error receiving a message.");
        }

        else
        {
                int pid = atoi(message.mtext);

                if(pid == getpid())
                {
                        return true;
                }

                else
                {
                        return false;
                }
        }
}

TimeType * MessageHandler::checkMessages()
{
        if(isChildProc)
        {
            throw Exception("Only the oss process can check messages.");
        }

        message_buf message;

        if(msgcrv(messageId, &message, 128, 3, IPC_NOWAIT) < 0)
        {
                if(errno == ENOMSG)
                {
                    return NULL;
                }

                else
                {
                    throw Exception("There was an error receiving a message.");
                }
        }

        else
        {
                TimeType *time = new TimeType();

                std::string str;
                std::size_t lock1;
                std::size_t lock2;

                str = message.mtext;

                lock1 = 0;
                lock2 = str.find("\t");

                if(lock2 == std::string::npos)
                {
                    throw Exception("There was an error decoding the message.");
                }

                time->pid = atoi(str.substr(lock1, lock2 - lock1).c_str());

                lock1 = lock2 + 1;
                lock2 = str.find("\t", lock1);

                if(lock2 == std::string::npos)
                {
                    throw Exception("There was an error decoding the message.");
                }

                time->seconds = atoi(str.substr(lock1, lock2 - lock1).c_str());

                lock1 = lock2 + 1;
                lock2 = str.length();

                time->nanoSeconds = atoi(str.substr(lock1, lock2 - lock1).c_str());

                return time;
        }
}

void MessageHandler::sendTimeMessage(TimeType time)
{
        if(!isChildProc) 
        {
            throw Exception("Only the child process can send a TimeType message.");
        }

        message_buf message;
        size_t messageLength;

        std::string str = std::to_string(getpid()) + "\t" + std::to_string(time.seconds) + "\t" std::to_string(time.nanoSeconds);

        message.mtype = 3;
        strcpy(message.mtext, str.c_str());
        messageLength = strlen(message.mtext) + 1;

        if(msgsnd(messageId, &message, messageLength, 0) < 0)
        {
            throw Exception("There was an error sending a time message.");
        }
}

void MessageHandler::close()
{
        if(isChildProc)
        {
            throw Exception("Only the master process can close the message handler.");
        }

        struct msqid_ds *buf;

        if(msgctl(messageId, IPC_RMID, buf) < 0)
        {
            throw Exception("There was an error closing the message queue.");
        }
}