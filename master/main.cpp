//Import Statements
#include <iostream>
#include <cstdlib>
#include <sys/wait.h>
#include <fstream>
#include "TimeType.h"
#include "Exception.h"
#include "SharedMem.h"
#include "ArgumentHandler.h"
#include "ChildProcessHandler.h"
#include "MessageHandler.h"
#include "HelpDisplay.h"

using namespace std;

//Function Declaration
void getMessage(string, TimeType, TimeType *);

int main(int argc, char** argv)
{
        try
        {
                ArgumentHandler args (argc, argv);

                if(HelpDisplay::print(args.getHelpFlag()))
                {
                        return 0;
                }

                ChildProcessHandler processes (args.getNumChildProcs());
                SharedMem clock;
                MessageHandler message;

                processes.startChildProcesses();

                int status;
                bool lock = false;

                while(processes.numRunningChildren() > 0)
                {
                        if(!lock)
                        {
                                lock = message.grantCriticalSection();
                        }

                        TimeType *t = message.checkMessages();

                        if(t != NULL)
                        {
                                getMessage(args.getFilename(), clock.getTime(), t);
                                lock = false;
                        }

                        clock.increment();

                        pid_t pid = waitpid((pid_t)-1, &status, WNOHANG);

                        if(pid > 0)
                        {
                                processes.removeTerminatedChild(pid);
                        }

                        processes.startChildIfNeeded();
                }

                clock.close();
                message.close();
        }

        catch(const Exception e)
        {
                cerr << e.what() << endl;
                return 1;
        }

        return 0;
}

//Function to get the message
void getMessage(string filename, TimeType now, TimeType *time)
{
        ofstream file;
        file.open(filename, ios::out | ios::app);
        file << "Master: Child " << time->pid << " is terminating at time " << now.seconds << "." << now.nanoSeconds << " because it reached " << endl;
        time->seconds << "." << time->nanoSeconds << " in slave" << endl;
        file.close();
}