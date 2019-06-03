#ifndef PrimitiveObjects_hpp
#define PrimitiveObjects_hpp

#include <glm/glm.hpp>

#include "Game.hpp"
#include "GameObject.hpp"
#include "IPosition.hpp"

class PrimitiveObjects
{
public:
    static GameObject * CreateSteve();
public:
    static GameObject * CreateSphereDummy();
public:
    static GameObject * CreateStageDummy();
    static GameObject * CreateCamera();
    static void GenerateBallsForLevel(Vector3 centerPosition, float laenge, float breite);
};

#endif /* PrimitiveObjects_hpp */
