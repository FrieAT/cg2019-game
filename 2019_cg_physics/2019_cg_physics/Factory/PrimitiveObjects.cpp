#include "PrimitiveObjects.hpp"
#include "ObjectManager.hpp"
//#include "DummyTriangleDrawing.hpp"
#include "DummyCubeDrawing.hpp"
#include "DummyTriangleDrawing.hpp"

GameObject * PrimitiveObjects::CreateTriangleDummy()
{
    GameObject * g = new GameObject("Triangle", "Opaque");
    
    g->SetComponent(new DummyTriangleDrawing());
    
    return g;
}

GameObject * PrimitiveObjects::CreateCubeDummy()
{
    GameObject * g = new GameObject("Cube", "Opaque");
    
    g->SetComponent(new DummyCubeDrawing());
    
    return g;
}
