#ifndef PrimitiveObjects_hpp
#define PrimitiveObjects_hpp

#include "Game.hpp"
#include "GameObject.hpp"

class PrimitiveObjects
{
public:
    static GameObject * CreateTriangleDummy();
    static GameObject * CreateCubeDummy();
};

#endif /* PrimitiveObjects_hpp */
