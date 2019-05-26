#ifndef PrimitiveObjects_hpp
#define PrimitiveObjects_hpp

#include <glm/glm.hpp>

#include "Game.hpp"
#include "GameObject.hpp"

typedef glm::fvec3 Vector3;

class PrimitiveObjects
{
public:
    static GameObject * CreateCubeDummy();
public:
    static GameObject * CreateSphereDummy();
public:
    static GameObject * CreateStageDummy();
    static GameObject * CreateCamera();
    static void GenerateBallsForLevel(Vector3 centerPosition, float laenge, float breite);
};

#endif /* PrimitiveObjects_hpp */
