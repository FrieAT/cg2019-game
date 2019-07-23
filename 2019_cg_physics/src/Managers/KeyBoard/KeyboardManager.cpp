//
//  KeyBoardManager.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 09.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.hpp"

#include "WindowManager.hpp"

#include "KeyboardManager.hpp"
#include "IPlayer.hpp"
#include "IMovement.hpp"
#include "ObjectManager.hpp"
#include "IView.hpp"

Vector2 KeyboardManager::_dir = Vector2(0.0f);

KeyboardManager::KeyboardManager(const Game & engine)
: AbstractManager(engine)
{
    KeyboardManager::_dir = Vector2(0.0f);
}

void KeyboardManager::Initialize()
{
    auto windowManager = GetEngine().GetManager<WindowManager>();
    
    auto window = windowManager->GetWindow();
    
    glfwSetKeyCallback(window, KeyboardManager::keyCallbackM);
}

void KeyboardManager::Loop()
{
    auto objectManager = Game::GetEngine()->GetManager<ObjectManager>();
    //auto windowManager = Game::GetEngine()->GetManager<WindowManager>();
    
    auto objects = objectManager->GetObjectsByName("Opaque");
    auto it = objects.begin();
    while(it != objects.end()) {
        
        auto player = dynamic_cast<IPlayer*>((*it)->GetComponent(EComponentType::Player));
        auto movement = dynamic_cast<IMovement*>((*it)->GetComponent(EComponentType::Movement));
        auto position = dynamic_cast<IPosition*>((*it)->GetComponent(EComponentType::Position));
        
        if(player != nullptr && movement != nullptr) {
          
            float speed = 4.5f;
            Vector3 velocity = Vector3(_dir.x, 0.0, _dir.y) * GetEngine().GetDeltaTime() * speed;
          
            
            auto cameras = objectManager->GetObjectsByName("Camera");
            
            auto cameraIt = cameras.begin();
            while(cameraIt != cameras.end())
            {
                auto view = dynamic_cast<IView*>((*cameraIt)->GetComponent(EComponentType::View));
                
                if(view != nullptr) {
                    Vector3 newLookAt = position->GetPosition() + Vector3(0.0f, 0.7f, 0.0f);
                    view->LookAt(newLookAt);
                }
                
                cameraIt++;
            }
            
            // Fence boundary check. Primitive.
            Vector3 newPosition = position->GetPosition() + velocity;
            if(newPosition.x <= -2.4) {
                newPosition.x = -2.4f;
                velocity = newPosition - position->GetPosition();
            } else if(newPosition.x >= 2.4) {
                newPosition.x = 2.4f;
                velocity = newPosition - position->GetPosition();
            }
            if(newPosition.z > 0.9) {
                newPosition.z = 0.9f;
                velocity = newPosition - position->GetPosition();
            } else if(newPosition.z < -0.9) {
                newPosition.z = -0.9;
                velocity = newPosition - position->GetPosition();
            }
            
            movement->SetVelocity(velocity);
            //position->AddRotation(ERotation::Pitch, rotation);
        }
        
        it++;
    }
    
}

void KeyboardManager:: keyCallbackM(GLFWwindow* myWindow, int key, int scanCode, int action, int mod)
{
    if (((key == GLFW_KEY_ESCAPE) || (key == GLFW_KEY_Q)) && (action == GLFW_PRESS))
    /* close window upon hitting the escape key or Q/q */
        glfwSetWindowShouldClose(myWindow, GL_TRUE);
    if ((key == GLFW_KEY_RIGHT) && action == GLFW_PRESS) {
        _dir += Vector2(1.0f, 0.0f);
    } else if (key == GLFW_KEY_RIGHT && action != GLFW_REPEAT) {
        _dir -= Vector2(1.0f, 0.0f);
    }
    
    if ((key == GLFW_KEY_LEFT) && action == GLFW_PRESS) {
        _dir -= Vector2(1.0f, 0.0f);
    } else if (key == GLFW_KEY_LEFT && action != GLFW_REPEAT) {
        _dir += Vector2(1.0f, 0.0f);
    }
    
    if ((key == GLFW_KEY_DOWN) && action == GLFW_PRESS) {
        _dir += Vector2(0.0f, 1.0f);
    } else if (key == GLFW_KEY_DOWN && action != GLFW_REPEAT) {
        _dir -= Vector2(0.0f, 1.0f);
    }
    
    if ((key == GLFW_KEY_UP) && action == GLFW_PRESS) {
        _dir -= Vector2(0.0f, 1.0f);
    } else if (key == GLFW_KEY_UP && action != GLFW_REPEAT) {
        _dir += Vector2(0.0f, 1.0f);
    }
}
