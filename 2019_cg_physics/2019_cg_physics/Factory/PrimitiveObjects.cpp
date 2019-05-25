#include "PrimitiveObjects.hpp"
#include "ObjectManager.hpp"
#include "CubeDrawing.hpp"
#include "SphereDrawing.hpp"
#include "StageDrawing.hpp"
#include "PixelPosition.hpp"
#include "SphereShader.hpp"
#include "PrototypeView.hpp"
#include "LinearMovement.hpp"
#include "IPlayer.hpp"

GameObject * PrimitiveObjects::CreateStageDummy()
{
    GameObject * g = new GameObject("Stage", "Opaque");
    
    g->SetComponent(new SphereShader());
    g->SetComponent(new PixelPosition());
    g->SetComponent(new StageDrawing());
    
    return g;
}
GameObject * PrimitiveObjects::CreateTriangleDummy()
{
    GameObject * g = new GameObject("Triangle", "Opaque");
    
    g->SetComponent(new CubeDrawing());
    g->SetComponent(new PixelPosition());
    auto movement = new LinearMovement();
    movement->SetSpeed(0.23f);
    g->SetComponent(movement);
    g->SetComponent(new IPlayer());
    //g->SetComponent(new DummyTriangleDrawing());
    
    return g;
}
GameObject * PrimitiveObjects::CreateSphereDummy()
{
    GameObject * g = new GameObject("Sphere", "Opaque");
    
    g->SetComponent(new SphereShader());
    g->SetComponent(new SphereDrawing());
    g->SetComponent(new PixelPosition());
    
    return g;
}

GameObject * PrimitiveObjects::CreateCamera()
{
    GameObject * g = new GameObject("Camera", "Camera");
    
    auto position = new PixelPosition();
    position->SetPosition(Vector3(0.0f, 2.0f, 3.9f));
    g->SetComponent(position);
    
    auto view = new PrototypeView();
    view->SetProjection(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 10.0f);
    view->LookAt(Vector3(0.0f, 1.0f, 0.0f));
    g->SetComponent(view);
    
    return g;
}


