#include "PrimitiveObjects.hpp"
#include "ObjectManager.hpp"
#include "CubeDrawing.hpp"
#include "SphereDrawing.hpp"
#include "StageDrawing.hpp"
GameObject * PrimitiveObjects::CreateStageDummy()
{
    GameObject * g = new GameObject("Stage", "Opaque");
    
    g->SetComponent(new StageDrawing());
    
    return g;
}
GameObject * PrimitiveObjects::CreateTriangleDummy()
{
    GameObject * g = new GameObject("Triangle", "Opaque");
    
    g->SetComponent(new CubeDrawing());
    
    return g;
}
GameObject * PrimitiveObjects::CreateSphereDummy()
{
    GameObject * g = new GameObject("Sphere", "Opaque");
    
    g->SetComponent(new SphereDrawing());
    
    return g;
}

void PrimitiveObjects::GenerateBallsForLevel(Vector3 centerPosition, float laenge, float breite)
{
    float ballSize = 5;
    float startingHeight = 4.0;
    for(float y = centerPosition.y - laenge; y < centerPosition.y + laenge; y+=ballSize) {
        for(float x = centerPosition.x - breite; x < centerPosition.x + breite; x+=ballSize) {
            GameObject* p = CreateSphereDummy();
            /*
            auto position = dynamic_cast<IPosition*>(p->GetComponent(EComponentType::Position));
            position->SetPosition(Vector3(x, y, startingHeight));
             */
        }
    }
}
