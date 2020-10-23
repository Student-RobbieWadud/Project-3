#include "TimeType.h"

TimeType::TimeType()
{
        seconds = 0;
        nanoSeconds = 0;
}

TimeType::TimeType(int s, long n)
{
        seconds = s;
        nanoSeconds = n;
}

TimeType TimeType::operator +(const TimeType &param)
{
        TimeType temp;

        temp.seconds = seconds + param.seconds;
        temp.nanoSeconds = nanoSeconds + param.nanoSeconds;

        while(temp.nanoSeconds > 999999999)
        {
                temp.seconds++;
                temp.nanoSeconds = temp.nanoSeconds - 1000000000;
        }

        return temp;
}

bool TimeType::operator <(const TimeType &param)
{
        if(seconds < param.seconds)
        {
                return true;
        }

        else if(seconds > param.seconds)
        {
                return false;
        }

        else
        {
                if(nanoSeconds < param.nanoSeconds)
                {
                        return true;
                }

                else
                {
                        return false;
                }
        }
}

bool TimeType::operator >(const TimeType &param)
{
        if(seconds > param.seconds)
        {
                return true;
        }

        else if(seconds < param.seconds)
        {
                return false;
        }

        else
        {
                if(nanoSeconds > param.nanoSeconds)
                {
                        return true;
                }

                else
                {
                        return false;
                }
        }
}