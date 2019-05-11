#ifndef PrimitiveObjects_hpp
#define PrimitiveObjects_hpp

#include "Game.hpp"
#include "GameObject.hpp"

class PrimitiveObjects
{
public:
    static GameObject * CreateTriangleDummy();
public:
    static GameObject * CreateSphereDummy();
public:
    static GameObject * CreateStageDummy();
};

#endif /* PrimitiveObjects_hpp */
