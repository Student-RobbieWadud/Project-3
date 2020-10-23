#include <sys/shm.h>
#include <errno.h>
#include <string>
#include "SharedMem.h"
#include "Exception.h"
#include "TimeType.h"


SharedMem::SharedMem()
{
        isChildProc = false;
        setupSharedMem();
        setClock(0,0);
}

SharedMem::SharedMem(bool childProc)
{
        isChildProc = childProc;
        setupSharedMem();

        if(!isChildProc)
        {
                setClock(0,0);
        }
}

void SharedMem::setupSharedMem()
{
        key_t key;
        const int share_size = sizeof(int) + sizeof(long);
        int *sharedMem;

        if((key = ftok(".", 1)) == (key_t) -1) throw Exception("There was an error setting the shared memory key:" + std::to_string(errno));

        segmentId = shmget(key, share_size, 0777 | IPC_CREAT);

        if(segmentId < 0) throw Exception("There was an error getting the shared memory segment.");

        sharedMem = (int*) shmat(segmentId, NULL, 0);

        if(sharedMem == (int*)-1) throw Exception("There was an error attaching the shared memory segment.");

        seconds = sharedMem + 0;
        nanoSeconds = (long*) (sharedMem + 1);
}

void SharedMem::setClock(int s, int n)
{
        if(isChildProc) throw Exception("The child process cannot modify the shared memory.");

        *seconds = s;
        *nanoSeconds = n;
}

int SharedMem::getSeconds()
{
        int s;
        s = *seconds;
        return s;
}

long SharedMem::getNanoSeconds()
{
        int n;
        n = *nanoSeconds;
        return n;
}

TimeType SharedMem::getTime()
{
        TimeType time(getSeconds(), getNanoSeconds());
        return time;
}

void SharedMem::increment()
{
        if(isChildProc) throw Exception("The child process cannot change the shared memory.");

        long increment_amount = 100000;

        if(*nanoSeconds == 999999999)
        {
                (*seconds)++;
                *nanoSeconds = 0;
        }

        else
        {
                *nanoSeconds += increment_amount;

                if(*nanoSeconds > 999999999)
                {
                        (*seconds)++;
                        *nanoSeconds -= 1000000000;
                }
        }
}

void SharedMem::close()
{
        if(isChildProc) throw Exception("Only the master process can remove shared memory.");

        int *sharedInt = (int *) shmat(segmentId, NULL, 0);

        shmdt(sharedInt);

        shmctl(segmentId, IPC_RMID, NULL);
}