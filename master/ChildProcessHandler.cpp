//Import Statements
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "ChildProcessHandler.h"
#include "Exception.h"

//Namespace acting weird, just won't use it. Will create functions differently.


ChildProcessHandler::ChildProcessHandler(int numberOfChildren)
{
        children = numberOfChildren;
        exeCounter = 0;
}

void ChildProcessHandler::startChildProcesses()
{
        for(int counter = 0; counter < children; counter++)
        {
                startNewChild();
        }
}

void ChildProcessHandler::startNewChild()
{
        int pid = fork();

        if(pid == 0)
        {
                execl("child", "child", NULL);
                throw Exception("There was an error starting the child process.");
        }

        pids.push_back(pid);
        exeCounter++;
}

void ChildProcessHandler::startChildIfNeeded()
{
        while(pids.size() < children && exeCounter < 100)
        {
                startNewChild();
        }
}

void ChildProcessHandler::removeTerminatedChild(int pid)
{
        for(int counter = 0; counter < pids.size(); counter++)
        {
                if(pids[counter] == pid)
                {
                        pids.erase(pids.begin() + counter);
                        break;
                }
        }
}

void ChildProcessHandler::printPids()
{
        for(int counter = 0; counter < pids.size(); counter++)
        {
                std::cout << pids[counter] << std::endl;
        }
}

//Functions to return certain vars

int ChildProcessHandler::numRunningChildren()
{
        return pids.size();
}

std::vector<int> ChildProcessHandler::getPids()
{
        return pids;
}