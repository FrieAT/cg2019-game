#include "PrimitiveObjects.hpp"
#include "DummyTriangleDrawing.hpp"

GameObject * PrimitiveObjects::CreateTriangleDummy(const Game & engine)
{
    GameObject * g = new GameObject("test", "test");
    
    g->SetComponent(new DummyTriangleDrawing());
    
    
    
    return g;
}
