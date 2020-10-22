#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include "Exception.h"
#include "ArgumentHandler.h"
#include "HelpDisplay.h"
#include "ChildProcessHandler.h"
#include "SharedMem.h"
#include "MessageHandler.h"
#include "TimeType.h"

using namespace std;

void record_message(string, TimeType, TimeType *);

int main(int argc, char** argv)
{
        try
        {
                ArgumentHandler args (argc, argv);

                if(HelpDisplay::print(args.getHelpFlag())) return 0;

                ChildProcessHandler processes (args.getNumChildProcs());
                MessageHandler message;
                SharedMem clock;

                processes.startChildProcesses();

                int status;
                bool lock = false;

                while(processes.numRunningChildren() > 0)
                {
                        if(!lock) lock = message.grantCriticalSection();

                        TimeType *t = message.checkMessages();

                        if(t != NULL)
                        {
                                record_message(args.getFilename(), clock.getTime(), t);
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

void record_message(string filename, TimeType current_time, TimeType *time)
{
        ofstream file;
        file.open(filename, ios::out | ios::app);
        file << "Master: Child " << time->pid << " is terminating at time " << current_time.seconds << "." << current_time.nanoSeconds << " because it reached " << time->seconds << "." << time->nanoSeconds << " in slave" << endl;
        file.close();
}