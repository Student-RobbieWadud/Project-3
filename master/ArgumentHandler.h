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
        bool help_flag;
        int num_child_procs;
        std::string filename;
        int term_time;
};

#endif /* ARGUMENTHANDLER_H */