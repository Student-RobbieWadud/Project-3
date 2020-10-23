#ifndef CHILDPROCESSHANDLER_H
#define CHILDPROCESSHANDLER_H

//Import Statement
#include <vector>

class ChildProcessHandler
{
public:
        ChildProcessHandler(int);
        void startChildProcesses();
        void startNewChild();
        void startChildIfNeeded();

        std::vector<int> getPids();

        void removeTerminatedChild(int);
        int numRunningChildren();
        void printPids();
private:
        int children, exeCounter;
        std::vector<int> pids;
};

#endif /* CHILDPROCESSHANDLER_H */