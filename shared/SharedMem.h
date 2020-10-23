#ifndef SHAREDMEM_H
#define SHAREDMEM_H

//Import Statements
#include <sys/shm.h>
#include "TimeType.h"

class SharedMem
{
public:
        SharedMem();
        SharedMem(bool);
        void setClock(int, int);
        int getSeconds();
        long getNanoSeconds();
        TimeType getTime();
        void increment();
        void close();
private:
        void setupSharedMem();
        bool isChildProc;
        int segmentId;
        int *seconds;
        long *nanoSeconds;
};

#endif /* SHAREDMEM_H */