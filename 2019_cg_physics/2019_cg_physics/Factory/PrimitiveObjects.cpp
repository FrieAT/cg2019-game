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


