#ifndef PrimitiveObjects_hpp
#define PrimitiveObjects_hpp

#include "glm/glm.hpp"

#include "Game.hpp"
#include "GameObject.hpp"
#include "IPosition.hpp"
#include "ObjectManager.hpp"

#include <GL/glew.h>

class PrimitiveObjects
{
public:
    static GameObject * CreateSteve();
public:
    static GameObject * CreateSphereDummy();
public:
    static GameObject * CreateGeometrie();
public:
    static GameObject * CreateStageDummy();
    static GameObject * CreateCamera();
    static GameObject * CreateGrass();
    static GameObject * CreateGameOverBlock();
    static void GenerateBallsForLevel(ObjectManager * manager, Vector3 centerPosition, float laenge, float breite);
    static void GenerateLandschaft(ObjectManager * manager, Vector3 centerPosition, float laenge, float breite);
    

    static void GenerateFenceAroundField(ObjectManager * manager);
};

#endif /* PrimitiveObjects_hpp */
