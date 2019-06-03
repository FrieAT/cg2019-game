#ifndef PrimitiveObjects_hpp
#define PrimitiveObjects_hpp

#include <glm/glm.hpp>

#include "Game.hpp"
#include "GameObject.hpp"
#include "IPosition.hpp"
#include "ObjectManager.hpp"

class PrimitiveObjects
{
public:
    static GameObject * CreateSteve();
public:
    static GameObject * CreateSphereDummy();
public:
    static GameObject * CreateStageDummy();
    static GameObject * CreateCamera();
    static void GenerateBallsForLevel(ObjectManager * manager, Vector3 centerPosition, float laenge, float breite);
};

#endif /* PrimitiveObjects_hpp */
