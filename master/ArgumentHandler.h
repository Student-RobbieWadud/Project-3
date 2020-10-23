#ifndef ARGUMENTHANDLER_H
#define ARGUMENTHANDLER_H

#include <string>

class ArgumentHandler
{
public:
        ArgumentHandler(int, char**);
        bool getHelpFlag();
        int getNumChildProcs();
        std::string getFilename();
        int getTerminationTime();
private:
        bool flag;
        int childProcesses;
        std::string filename;
        int termination;
};

#endif /* ARGUMENTHANDLER_H */