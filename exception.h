#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

class MException : public std::exception
{
    std::string message;
public:
    MException();
    explicit MException(std::string str);

    friend std::ostream& operator <<(std::ostream &os, MException &exc);
};
#endif // EXCEPTION_H
