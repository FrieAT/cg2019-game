//
//  Exception.h
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 01.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

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
