#ifndef TIMETYPE_H
#define TIMETYPE_H

class TimeType
{
public:
        TimeType();
        TimeType(int, long);
        TimeType operator + (const TimeType &);
        bool operator < (const TimeType &);
        bool operator > (const TimeType &);
        int pid;
        int seconds;
        long nanoSeconds;
private:

};

#endif /* TIMETYPE_H */