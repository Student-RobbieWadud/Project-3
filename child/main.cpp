#include <cstdlib>
#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "SharedMem.h"
#include "TimeType.h"
#include "MessageHandler.h"

using namespace std;

int generateWaitTime();
TimeType criticalSection(SharedMem);

int main(int argc, char** argv)
{
        SharedMem clock(true);
        MessageHandler message(true);

        message.requestCriticalSection();
        message.receiveCriticalSection();

        TimeType t = criticalSection(clock);

        message.sendTimeMessage(t);

        return 0;
}

int generateWaitTime()
{
        int low_num = 1;
        int high_num = 100000;

        srand(time(NULL) + getpid());

        return ((rand() % (high_num - low_num)) + low_num);
}

TimeType criticalSection(SharedMem clock)
{
        TimeType wait_time(0, generateWaitTime());
        TimeType current_time = clock.getTime();
        TimeType end_time = current_time + wait_time;

        do
        {
                current_time = clock.getTime();
        } while(current_time < end_time);

        return end_time;
}