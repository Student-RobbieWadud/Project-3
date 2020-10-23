               return true;
        }
}

bool MessageHandler::receiveCriticalSection()
{
        if(!isChildProc) throw Exception("Only the child process can request the critical section.");

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
        if(isChildProc) throw Exception("Only the oss process can check messages.");

        message_buf message;

        if(msgcrv(messageId, &message, 128, 3, IPC_NOWAIT) < 0)
        {
                if(errno == ENOMSG) return NULL;
                else throw Exception("There was an error receiving a message.");
        }

        else
        {
                TimeType *time = new TimeType();

                std::string str;
                std::size_t loc1;
                std::size_t loc2;

                str = message.mtext;

                loc1 = 0;
                loc2 = str.find("\t");

                if(loc2 == std::string::npos) throw Exception("There was an error decoding the message.");

                time->pid = atoi(str.substr(loc1, loc2 - loc1).c_str());

                loc1 = loc2 + 1;
                loc2 = str.find("\t", loc1);

                if(loc2 == std::string::npos) throw Exception("There was an error decoding the message.");

                time->seconds = atoi(str.substr(loc1, loc2 - loc1).c_str());

                loc1 = loc2 + 1;
                loc2 = str.length();

                time->nanoSeconds = atoi(str.substr(loc1, loc2 - loc1).c_str());

                return time;
        }
}

void MessageHandler::sendTimeMessage(TimeType time)
{
        if(!isChildProc) throw Exception("Only the child process can send a TimeType message.");

        message_buf message;
        size_t message_len;

        std::string str = std::to_string(getpid()) + "\t" + std::to_string(time.seconds) + "\t" std::to_string(time.nanoSeconds);

        message.mtype = 3;
        strcpy(message.mtext, str.c_str());
        message_len = strlen(message.mtext) + 1;

        if(msgsnd(messageId, &message, message_len, 0) < 0) throw Exception("There was an error sending a time message.");
}

void MessageHandler::close()
{
        if(isChildProc) throw Exception("Only the master process can close the message handler.");

        struct msqid_ds *buf;

        if(msgctl(messageId, IPC_RMID, buf) < 0) throw Exception("There was an error closing the message queue.");
}