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
#include <sstream>
//#include "SphereDrawing.hpp"
#include "GrassBlockTexture.hpp"
#include "GameOverBlockTexture.hpp"
#include "WoodBlockTexture.hpp"
#include "SteveArmAnimation.hpp"
#include "SteveLegAnimation.hpp"

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

GameObject * PrimitiveObjects::CreateGrass()
{
    PixelTransform * transform;
    IDrawing * drawing;
    
    GameObject * g = new GameObject("Grass", "Opaque");
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 0.5f, 0.5f));
    transform->SetPosition(Vector3(0.0, 0.5, -1.0));
    g->SetComponent(new SphereShader());
    g->SetComponent(transform);
    drawing = new CubeDrawing();
    drawing->SetTexture(new GrassBlockTexture());
    g->SetComponent(drawing);
    
    return g;
}

GameObject * PrimitiveObjects::CreateGameOverBlock()
{
    PixelTransform * transform;
    IDrawing * drawing;
    
    GameObject * go = new GameObject("GameOver", "Opaque");
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 0.5f, 0.5f));
    transform->SetPosition(Vector3(0.0, 0.5, -1.0));
    go->SetComponent(new SphereShader());
    go->SetComponent(transform);
    drawing = new CubeDrawing();
    drawing->SetTexture(new GameOverBlockTexture());
    go->SetComponent(drawing);
    
    return go;
}

GameObject * PrimitiveObjects::CreateSteve()
{
    std::string renderLayer = "Opaque";
    PixelTransform * transform;
    SphereShader * usedShader;
    IDrawing * drawing;
    IAnimation * animation;
    
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
    animation = new SteveLegAnimation();
    animation->SetForward(false);
    leftLeg->SetComponent(animation);
    
    GameObject * rightLeg = new GameObject("sRightLeg", renderLayer);
    transform = new PixelTransform();
    transform->SetScale(Vector3(0.5f, 1.5f, 0.5f));
    transform->SetPosition(Vector3(0.25f, 0.75f, 0.0f));
    rightLeg->SetComponent(transform);
    rightLeg->SetComponent(usedShader);
    drawing = new CubeDrawing();
    drawing->SetTexture(new SteveLegTexture());
    rightLeg->SetComponent(drawing);
    animation = new SteveLegAnimation();
    animation->SetForward(true);
    rightLeg->SetComponent(animation);
    
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
    animation = new SteveArmAnimation();
    //animation->SetInitialRotation(45.0f);
    animation->SetForward(true);
    leftArm->SetComponent(animation);
    
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
    animation = new SteveArmAnimation();
    //animation->SetInitialRotation(-45.0f);
    animation->SetForward(false);
    rightArm->SetComponent(animation);
    
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

void PrimitiveObjects::GenerateLandschaft(ObjectManager * manager, Vector3 centerPosition, float laenge, float breite)
{
    float cubeSize = 0.5;
    for(float y = -4.0f ; y < centerPosition.z; y+=cubeSize*2.0f) {
        for(float x = centerPosition.x - breite; x < centerPosition.x + breite; x+=cubeSize*2.0f) {
            if(rand() % 100 < 0) {
                continue;
            }
            int created = 0;
            for(int i = 0; i < 2; i++) {
                if(rand() % 100 > i * 45) {
                    continue;
                }
                
                
                
                GameObject* p = CreateGrass();
                IPosition * transform = dynamic_cast<IPosition*>(p->GetComponent(EComponentType::Position));
                transform->SetPosition(Vector3(x, 0.25f + 0.5f * created, y));
                manager->AddGameObject(p);
                created++;
            }
        }
        
        // Game Over Object in Planar
        GameObject* go = CreateGameOverBlock();
        IPosition * transforme= dynamic_cast<IPosition*>(go->GetComponent(EComponentType::Position));
        transforme->SetPosition(Vector3(0.0f, 0.25f + 0.5f, 0.0f));
        manager->AddGameObject(go);
    }
}

//void PrimitiveObjects::GenerateLandschaft(ObjectManager * manager, Vector3 centerPosition, float laenge, float breite)
//{
//    float cubeSize = 0.5;
//    for(float y = centerPosition.y - laenge; y < centerPosition.y + laenge; y+=cubeSize*2.0f) {
//        for(float x = centerPosition.x - breite; x < centerPosition.x + breite; x+=cubeSize*2.0f) {
//            if(rand() % 100 < 20) {
//                continue;
//            }
//            int created = 0;
//            for(int i = 0; i < 2; i++) {
//                if(rand() % 100 > i * 15) {
//                    continue;
//                }
//                GameObject* p = CreateGrass();
//                IPosition * transform = dynamic_cast<IPosition*>(p->GetComponent(EComponentType::Position));
//                transform->SetPosition(Vector3(x, 0.25f + 0.5f * created, y));
//                manager->AddGameObject(p);
//                created++;
//            }
//        }
//    }
//}


void PrimitiveObjects::GenerateFenceAroundField(ObjectManager * manager)
{
    std::string renderLayer = "Opaque";
    PixelTransform * transform;
    SphereShader * usedShader;
    IDrawing * drawing;
    GameObject * child;
    
    float coordinates[12][6] = {
        {-2.5f, 0.35f, 1.0f, 0.1f, 0.7f, 0.1f}, // left front
        {2.5f, 0.35f, 1.0f, 0.1f, 0.7f, 0.1f}, // right front
        {-2.5f, 0.35f, -1.0f, 0.1f, 0.7f, 0.1f}, // left back
        {2.5f, 0.35f, -1.0f, 0.1f, 0.7f, 0.1f}, // right back
        
        // back sprouts
        {0.0f, 0.50f, -1.0f, 5.0f, 0.1f, 0.1f},
        {0.0f, 0.30f, -1.0f, 5.0f, 0.1f, 0.1f},
        
        // front sprouts
        {0.0f, 0.50f, 1.0f, 5.0f, 0.1f, 0.1f},
        {0.0f, 0.30f, 1.0f, 5.0f, 0.1f, 0.1f},
        
        // left sprouts
        {-2.5f, 0.50f, 0.0f, 0.1f, 0.1f, 2.0f},
        {-2.5f, 0.30f, 0.0f, 0.1f, 0.1f, 2.0f},
        
        // right sprouts
        {2.5f, 0.50f, 0.0f, 0.1f, 0.1f, 2.0f},
        {2.5f, 0.30f, 0.0f, 0.1f, 0.1f, 2.0f},
    };
    

    
    GameObject * g = new GameObject("FenceCenter", renderLayer);
    usedShader = new SphereShader();
    transform = new PixelTransform();
    //transform->SetScale(Vector3(1.0f));
    transform->SetPosition(Vector3(0.0, 0.0, 0.0));
    g->SetComponent(usedShader);
    g->SetComponent(transform);
    
    for(int object = 0; object < 12; object++) {
        std::stringstream ss;
        ss << "fencePart_" << object;
        child = new GameObject(ss.str(), renderLayer);
        transform = new PixelTransform();
        transform->SetPosition(Vector3(coordinates[object][0], coordinates[object][1], coordinates[object][2]));
        transform->SetScale(Vector3(coordinates[object][3], coordinates[object][4], coordinates[object][5]));
        child->SetComponent(transform);
        drawing = new CubeDrawing();
        drawing->SetTexture(new WoodBlockTexture());
        child->SetComponent(drawing);
        child->SetComponent(usedShader);
        g->AddChild(child);
    }
    
    manager->AddGameObject(g);
}
