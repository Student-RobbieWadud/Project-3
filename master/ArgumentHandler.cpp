#include <string>
#include <cstdlib>
#include <unistd.h>
#include "ArgumentHandler.h"
#include "Exception.h"

ArgumentHandler::ArgumentHandler(int argc, char** argv)
{
        help_flag = false;
        num_child_procs = 5;
        filename = "test.out";
        term_time = 20;

        int c;
        opterr = 0;
        std::string opt;
        std::string str;

        while((c = getopt(argc, argv, "hs:l:t")) != -1)
        {
                switch(c)
                {
                        case 'h':
                                help_flag = true;
                                break;

                        case 's':
                                str = optarg;
                                num_child_procs = atoi(str.c_str());
                                break;

                        case 'l':
                                filename = optarg;
                                break;

                        case 't':
                                str = optarg;
                                term_time = atoi(str.c_str());
                                break;

                        case '?':
                                opt = (char)optopt;

                                if(optopt == 's' || optopt == 'l' || optopt == 't')
                                        throw Exception("Option '" + opt + "' requires an argument.");

                                else if(isprint(optopt))
                                        throw Exception("Unknown option '" + opt + "'");

                                else
                                        throw Exception("Unknown option error.");
                                break;

                        default:
                                throw Exception("Unknown error");
                                break;
                }
        }

        for(int i = optind; i < argc; i++)
        {
                throw Exception("Too many arguments");
        }
}

bool ArgumentHandler::getHelpFlag()
{
        return help_flag;
}

int ArgumentHandler::getNumChildProcs()
{
        return num_child_procs;
}

std::string ArgumentHandler::getFilename()
{
        return filename;
}

int ArgumentHandler::getTerminationTime()
{
        return term_time;
}