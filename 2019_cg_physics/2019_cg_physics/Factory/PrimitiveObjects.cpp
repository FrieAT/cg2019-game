#include "PrimitiveObjects.hpp"
#include "ObjectManager.hpp"
#include "CubeDrawing.hpp"
#include "SphereDrawing.hpp"
#include "StageDrawing.hpp"
#include "PixelTransform.hpp"
#include "SphereShader.hpp"
#include "PrototypeView.hpp"
#include "DefaultShader.hpp"

GameObject * PrimitiveObjects::CreateStageDummy()
{
    GameObject * g = new GameObject("Stage", "Opaque");
    
    g->SetComponent(new SphereShader());
    g->SetComponent(new PixelTransform());
    g->SetComponent(new StageDrawing());
    
    return g;
}
GameObject * PrimitiveObjects::CreateSteve()
{
    std::string renderLayer = "Opaque";
    PixelTransform * transform;
    SphereShader * usedShader;
    
    GameObject * g = new GameObject("Steve", renderLayer);
    usedShader = new SphereShader();
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.3, 0.3f, 0.3));
    transform->SetPosition(Vector3(0.0, 0.0, 0.0));
    g->SetComponent(usedShader);
    g->SetComponent(transform);
    
    GameObject * head = new GameObject("sHead", renderLayer);
    transform = new PixelTransform();
    transform->SetPosition(Vector3(0.0f, 3.5f, 0.0f));
    //transform->SetScale(Vector3(0.5f, 0.3f, 0.5f));
    head->SetComponent(transform);
    head->SetComponent(new CubeDrawing());
    head->SetComponent(usedShader);
    
    GameObject * body = new GameObject("sBody", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(1.0f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(0.0f, 2.25f, 0.0f));
    body->SetComponent(transform);
    body->SetComponent(usedShader);
    body->SetComponent(new CubeDrawing());
    
    GameObject * leftLeg = new GameObject("sLeftLeg", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(-0.25f, 0.75f, 0.0f));
    leftLeg->SetComponent(transform);
    leftLeg->SetComponent(usedShader);
    leftLeg->SetComponent(new CubeDrawing());
    
    GameObject * rightLeg = new GameObject("sRightLeg", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(0.25f, 0.75f, 0.0f));
    rightLeg->SetComponent(transform);
    rightLeg->SetComponent(usedShader);
    rightLeg->SetComponent(new CubeDrawing());
    
    GameObject * leftArm = new GameObject("sLeftArm", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(-0.75f, 2.25f, 0.0f));
    leftArm->SetComponent(transform);
    leftArm->SetComponent(usedShader);
    leftArm->SetComponent(new CubeDrawing());
    
    GameObject * rightArm = new GameObject("sRightArm", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(0.75f, 2.25f, 0.0f));
    rightArm->SetComponent(transform);
    rightArm->SetComponent(usedShader);
    rightArm->SetComponent(new CubeDrawing());
    
    g->AddChild(head);
    g->AddChild(body);
    g->AddChild(leftLeg);
    g->AddChild(rightLeg);
    g->AddChild(leftArm);
    g->AddChild(rightArm);
    
    return g;
}
GameObject * PrimitiveObjects::CreateSphereDummy()
{
    GameObject * g = new GameObject("Sphere", "Opaque");
    
    g->SetComponent(new SphereShader());
    g->SetComponent(new SphereDrawing());
    g->SetComponent(new PixelTransform());
    
    return g;
}

GameObject * PrimitiveObjects::CreateCamera()
{
    GameObject * g = new GameObject("Camera", "Camera");
    
    auto position = new PixelTransform();
    position->SetPosition(Vector3(0.0f, 2.0f, 3.9f));
    g->SetComponent(position);
    
    auto view = new PrototypeView();
    view->SetProjection(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 10.0f);
    view->LookAt(Vector3(0.0f, 1.0f, 0.0f));
    g->SetComponent(view);
    
    return g;
}


