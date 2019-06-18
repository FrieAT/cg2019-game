#include "PrimitiveObjects.hpp"
#include "ObjectManager.hpp"
#include "CubeDrawing.hpp"
#include "Geometrie.hpp"
#include "SphereDrawing.hpp"
#include "StageDrawing.hpp"
#include "PixelTransform.hpp"
#include "SphereShader.hpp"
#include "PrototypeView.hpp"
#include "DefaultShader.hpp"
#include "LinearMovement.hpp"
#include "IPlayer.hpp"
#include "SteveHeadTexture.hpp"
#include "SteveBodyTexture.hpp"
#include "SteveLegTexture.hpp"
#include "SteveArmTexture.hpp"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "SphereDrawing.hpp"

     GLdouble times = glfwGetTime();
GameObject * PrimitiveObjects::CreateStageDummy()
{
    GameObject * g = new GameObject("Stage", "Opaque");
    
    g->SetComponent(new SphereShader());
    g->SetComponent(new PixelTransform());
    g->SetComponent(new StageDrawing());
    
    return g;
}

GameObject * PrimitiveObjects::CreateGeometrie()
{
    GameObject * g = new GameObject("Geometrie", "Opaque");
    
    g->SetComponent(new SphereShader());
    g->SetComponent(new PixelTransform());
    g->SetComponent(new Geometrie());
    
    return g;
}
GameObject * PrimitiveObjects::CreateSteve()
{
    std::string renderLayer = "Opaque";
    PixelTransform * transform;
    SphereShader * usedShader;
    IDrawing * drawing;
    
    GameObject * g = new GameObject("Steve", renderLayer);
    usedShader = new SphereShader();
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.3, 0.3f, 0.3));
    transform->SetPosition(Vector3(0.0, 0.0, 0.0));
    g->SetComponent(usedShader);
    g->SetComponent(transform);
    g->SetComponent(new LinearMovement());
    g->SetComponent(new IPlayer());
    
    GameObject * head = new GameObject("sHead", renderLayer);
    transform = new PixelTransform();
    transform->SetPosition(Vector3(0.0f, 3.5f, 0.0f));
    //transform->SetScale(Vector3(0.5f, 0.3f, 0.5f));
    head->SetComponent(transform);
    drawing = new CubeDrawing();
    drawing->SetTexture(new SteveHeadTexture());
    head->SetComponent(drawing);
    head->SetComponent(usedShader);
    
    GameObject * body = new GameObject("sBody", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(1.0f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(0.0f, 2.25f, 0.0f));
    body->SetComponent(transform);
    body->SetComponent(usedShader);
    drawing = new CubeDrawing();
    drawing->SetTexture(new SteveBodyTexture());
    body->SetComponent(drawing);
    
    GameObject * leftLeg = new GameObject("sLeftLeg", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(-0.25f, 0.75f, 0.0f));
    leftLeg->SetComponent(transform);
    leftLeg->SetComponent(usedShader);
    drawing = new CubeDrawing();
    drawing->SetTexture(new SteveLegTexture());
    leftLeg->SetComponent(drawing);
    
    GameObject * rightLeg = new GameObject("sRightLeg", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(0.25f, 0.75f, 0.0f));
    rightLeg->SetComponent(transform);
    rightLeg->SetComponent(usedShader);
    drawing = new CubeDrawing();
    drawing->SetTexture(new SteveLegTexture());
    rightLeg->SetComponent(drawing);
    
    GameObject * leftArm = new GameObject("sLeftArm", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(-0.75f, 2.25f, 0.0f));
    transform->SetRotation(ERotation::Yaw, 45.0);
    leftArm->SetComponent(transform);
    leftArm->SetComponent(usedShader);
    drawing = new CubeDrawing();
    drawing->SetTexture(new SteveArmTexture());
    leftArm->SetComponent(drawing);
    
    GameObject * rightArm = new GameObject("sRightArm", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(0.75f, 2.25f, 0.0f));
    transform->SetRotation(ERotation::Yaw, -45.0);
    rightArm->SetComponent(transform);
    rightArm->SetComponent(usedShader);
    drawing = new CubeDrawing();
    drawing->SetTexture(new SteveArmTexture());
    rightArm->SetComponent(drawing);
    
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

void PrimitiveObjects::GenerateBallsForLevel(ObjectManager * manager, Vector3 centerPosition, float laenge, float breite)
{ glfwSetTime( 0 );
    float ballSize = 0.3;
    float startingHeight = 4.0;
    for(float y = centerPosition.y - laenge; y < centerPosition.y + laenge; y+=ballSize*2.0f) {
        for(float x = centerPosition.x - breite; x < centerPosition.x + breite; x+=ballSize*2.0f) {
           double birthTime = glfwGetTime();
            GameObject* p = CreateSphereDummy();
            IPosition * transform = new PixelTransform();
            transform->SetPosition(Vector3(x, 3.0f, y));
            transform->SetScale(Vector3(ballSize));
            p->SetComponent(transform);
            manager->AddGameObject(p);
            
//            if( transform->GetPosition().z == -5.0f){
//              std::cout << transform->GetPosition().z<< "\n";
//                x = 1.0f * (times - birthTime) / 1.2f;
//                  std::cout << times<< "\n";  std::cout << birthTime<< "\n";
//
//                y =std::abs(2.0f *sinf(1.0f * (times - birthTime)+ 0.5f));
//                transform->SetPosition(Vector3(x, 3.0f, y));
////                transform->SetScale(Vector3(ballSize));
////                p->SetComponent(transform);
////                manager->AddGameObject(p);
          //  }
//
           
        }
    }

}


void PrimitiveObjects::GenerateGeometrieForLevel(ObjectManager * manager, Vector3 centerPosition, float laenge, float breite)
{
    float ballSize = 0.05;
    float startingHeight = 4.0;
    for(float y = centerPosition.y - laenge; y < centerPosition.y + laenge; y+=ballSize*2.0f) {
        for(float x = centerPosition.x - breite; x < centerPosition.x + breite; x+=ballSize*2.0f) {
            GameObject* p = CreateGeometrie();
            IPosition * transform = new PixelTransform();
            transform->SetPosition(Vector3(x, 0.0f, y));
            transform->SetScale(Vector3(ballSize));
            p->SetComponent(transform);
            manager->AddGameObject(p);
            //            auto position = dynamic_cast<IPosition*>(p->GetComponent(EComponentType::Position));
            //            position->SetPosition(Vector3(x, 3.0f, y));
            //            auto position = dynamic_cast<IPosition*>(p->GetComponent(EComponentType::Position));
            //            position->SetPosition(Vector3(x, y, startingHeight));
            
        }
    }
}
