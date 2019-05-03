#include "PrimitiveObjects.hpp"
#include "ObjectManager.hpp"
#include "DummyTriangleDrawing.hpp"

GameObject * PrimitiveObjects::CreateTriangleDummy()
{
    GameObject * g = new GameObject("Triangle", "Opaque");
    
    g->SetComponent(new DummyTriangleDrawing());
    
    return g;
}
