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

int KeyboardManager::_dir = -1;

KeyboardManager::KeyboardManager(const Game & engine)
: AbstractManager(engine)
, _mouseSpeedOrientation(0.005f)
, _mousePosState(0)
{
    KeyboardManager::_dir = -1;
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
    auto windowManager = Game::GetEngine()->GetManager<WindowManager>();
    
    auto objects = objectManager->GetObjectsByName("Opaque");
    auto it = objects.begin();
    while(it != objects.end()) {
        
        auto player = dynamic_cast<IPlayer*>((*it)->GetComponent(EComponentType::Player));
        auto movement = dynamic_cast<IMovement*>((*it)->GetComponent(EComponentType::Movement));
        auto position = dynamic_cast<IPosition*>((*it)->GetComponent(EComponentType::Position));
        
        if(player != nullptr && movement != nullptr) {
            //_dir = GetMoveDirection();
           // std::cout << _dir<< "\n";
            Vector3 velocity = Vector3(0.0, 0.0, 0.0);
            if(_dir == 0) velocity = Vector3(1.0, 0.0, 0.0);
            else if(_dir == 1) velocity = Vector3(-1.0, 0.0, 0.0);
            else if(_dir == 2) velocity = Vector3(0.0, 0.0, 1.0);
            else if(_dir == 3) velocity = Vector3(0.0, 0.0, -1.0);
            
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
            movement->SetVelocity(velocity);
        }
        
        it++;
    }
    
}

void KeyboardManager:: keyCallbackM(GLFWwindow* myWindow, int key, int scanCode, int action, int mod)
{
    if (((key == GLFW_KEY_ESCAPE) || (key == GLFW_KEY_Q)) && (action == GLFW_PRESS))
    /* close window upon hitting the escape key or Q/q */
        glfwSetWindowShouldClose(myWindow, GL_TRUE);
    else if ((key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS || GLFW_REPEAT== action)) {
        _dir = 0;
    } else if ((key == GLFW_KEY_LEFT) && (action == GLFW_PRESS|| GLFW_REPEAT== action)) {
        _dir = 1;
    } else if ((key == GLFW_KEY_DOWN) && (action == GLFW_PRESS || GLFW_REPEAT== action)) {
        _dir = 2;
    } else if ((key == GLFW_KEY_UP) && (action == GLFW_PRESS || GLFW_REPEAT== action)){
        _dir = 3;
    } else {
        _dir = -1;
    }
}
