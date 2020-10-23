#ifndef CHILDPROCESSHANDLER_H
#define CHILDPROCESSHANDLER_H

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
        int num_children;
        int exec_counter;
        std::vector<int> pids;
};

#endif /* CHILDPROCESSHANDLER_H */