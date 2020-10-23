#ifndef EXCEPTION_H
#define EXCEPTION_H

//Import Statements
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
        Exception(std::string e) {error=e; file = "unknown"; line = 0; fileline_set = false;}
        Exception(std::string e, std::string f, int l) {error = e; file = f; line = l;; fileline_set = true;}

        const char * what() const throw ()
        {
                std::string str;

                if(fileline_set)
                {
                        str = "There was an exception thrown: [" + file + ": " + std::to_string(line) + "]: " + error;
                }

                else
                {
                        str = "There was an exception thrown: " + error;
                }

                constant char * c = str.c_str();
                return c;
        }

        std::string error;
        std::string file;
        int line;
        bool fileline_set;
};

#endif /* EXCEPTION_H */