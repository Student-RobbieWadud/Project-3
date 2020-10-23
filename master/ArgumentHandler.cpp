//Import Statements
#include <unistd.h>
#include <cstdlib>
#include <string>
#include "Exception.h"
#include "ArgumentHandler.h"

//Namespace acting weird, just won't use it. Will create functions differently.

ArgumentHandler::ArgumentHandler(int argc, char** argv)
{
        //Creating the vars
        termination = 20;
        childProcesses = 5;
        flag = false;
        filename = "test.out";

        int userChar;
        opterr = 0;
        std::string opt;
        std::string str;

        //While loop for the options menu
        while((userChar = getopt(argc, argv, "hs:l:t")) != -1)
        {
                switch(userChar)
                {
                        case 'h':
                                flag = true;
                                break;

                        case 's':
                                str = optarg;
                                childProcesses = atoi(str.c_str());
                                break;

                        case 'l':
                                filename = optarg;
                                break;

                        case 't':
                                str = optarg;
                                termination = atoi(str.c_str());
                                break;

                        case '?':
                                opt = (char)optopt;

                                if(optopt == 's' || optopt == 'l' || optopt == 't')
                                        throw Exception("Option '" + opt + "' requires an argument.");

                                else if(isprint(optopt))
                                        throw Exception("Unknown option '" + opt + "'");

                                else
                                        throw Exception("There has been an unknown option error.");
                                break;

                        default:
                                throw Exception("This is an unknown error.");
                                break;
                }
        }

        //In case there are too many arguments...
        for(int counter = optind; counter < argc; counter++)
        {
                throw Exception("You have typed in too many arguments.");
        }
}

//Functions to return certain vars

bool ArgumentHandler::getHelpFlag()
{
        return flag;
}

int ArgumentHandler::getNumChildProcs()
{
        return childProcesses;
}

std::string ArgumentHandler::getFilename()
{
        return filename;
}

int ArgumentHandler::getTerminationTime()
{
        return termination;
}