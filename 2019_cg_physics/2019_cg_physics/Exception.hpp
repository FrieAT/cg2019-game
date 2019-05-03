#ifndef Exception_h
#define Exception_h

#include <string>
#include <exception>

class Exception : std::exception
{
public:
    Exception(std::string exceptionMessage);
    ~Exception() = default;
private:
    std::string _exceptionMessage;
};

#endif /* Exception_h */
