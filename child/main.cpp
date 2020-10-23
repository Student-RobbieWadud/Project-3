//Import Statements
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include "TimeType.h"
#include "MessageHandler.h"
#include "SharedMem.h"

using namespace std;

//Function Declarations
int getTime();
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

//Function to get the time.
int getTime()
{
        int high = 100000, low = 1;

        srand(time(NULL) + getpid());

        return ((rand() % (high - low)) + low);
}

//Function to calculate what should be in the critical section.
TimeType criticalSection(SharedMem clock)
{
        TimeType wait_time(0, getTime());
        TimeType now = clock.getTime(), endTime = now + wait_time;

        do
        {
                now = clock.getTime();
        } while(now < endTime);

        return endTime;
}