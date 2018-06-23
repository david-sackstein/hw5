#include "mathexception.h"

mathexception::mathexception(const char* msg) :
    msg_(msg)
{
}

const char* mathexception::what() const throw()
{
    return msg_.c_str();
}