#include "PrimitiveObjects.hpp"
#include "ObjectManager.hpp"
#include "DummyTriangleDrawing.hpp"
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
    
    g->SetComponent(new DummyTriangleDrawing());
    
    return g;
}
GameObject * PrimitiveObjects::CreateSphereDummy()
{
    GameObject * g = new GameObject("Sphere", "Opaque");
    
    g->SetComponent(new SphereDrawing());
    
    return g;
}


