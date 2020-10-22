#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "Exception.h"
#include "ChildProcessHandler.h"

ChildProcessHandler::ChildProcessHandler(int num_c)
{
        num_children = num_c;
        exec_counter = 0;
}

void ChildProcessHandler::startChildProcesses()
{
        for(int i = 0; i < num_children; i++)
        {
                startNewChild();
        }
}

void ChildProcessHandler::startNewChild()
{
        int pid;
        pid = fork();

        if(pid == 0)
        {
                execl(
                        "child",
                        "child",
                        NULL
                        );
                throw Exception("Error starting child process");
        }

        pids.push_back(pid);
        exec_counter++;
}

void ChildProcessHandler::startChildIfNeeded()
{
        while(pids.size() < num_children && exec_counter < 100)
        {
                startNewChild();
        }
}

void ChildProcessHandler::removeTerminatedChild(int pid)
{
        for(int i = 0; i < pids.size(); i++)
        {
                if(pids[i] == pid)
                {
                        pids.erase(pids.begin() + i);
                        break;
                }
        }
}

int ChildProcessHandler::numRunningChildren()
{
        return pids.size();
}

std::vector<int> ChildProcessHandler::getPids()
{
        return pids;
}

void ChildProcessHandler::printPids()
{
        for(int i = 0; i < pids.size(); i++)
        {
                std::cout << pids[i] << std::endl;
        }
}