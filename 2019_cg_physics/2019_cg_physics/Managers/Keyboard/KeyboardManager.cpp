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
, _orientation(Vector2(0.0f))
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
    
    // Source: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
    double halfWidth = windowManager->GetWindowWidth() / 2.0, halfHeight = windowManager->GetWindowHeight() / 2.0;
    double xpos, ypos;
    glfwGetCursorPos(windowManager->GetWindow(), &xpos, &ypos);
    Vector2 mouseOffset = Vector2(halfWidth - xpos, halfHeight - ypos);
    std::cout << "MouseOffsetLength: " << glm::length(mouseOffset) << std::endl;
    if(glm::length(mouseOffset) > 0.05f) {
        _orientation += mouseOffset * Game::GetEngine()->GetDeltaTime() * _mouseSpeedOrientation;
        Vector2 backToCenter = (Vector2(halfWidth, halfHeight) + mouseOffset) * Game::GetEngine()->GetDeltaTime();
        std::cout << "Cursor Pos #1 " << mouseOffset.x << " and " << mouseOffset.y << std::endl;
        std::cout << "Cursor Pos #2 " << xpos << " and " << ypos << std::endl;
        glfwSetCursorPos(windowManager->GetWindow(), xpos + mouseOffset.x * Game::GetEngine()->GetDeltaTime(), ypos + mouseOffset.y * Game::GetEngine()->GetDeltaTime());
    }
        
    auto objects = objectManager->GetObjectsByName("Opaque");
    auto it = objects.begin();
    while(it != objects.end()) {
        
        auto player = dynamic_cast<IPlayer*>((*it)->GetComponent(EComponentType::Player));
        auto movement = dynamic_cast<IMovement*>((*it)->GetComponent(EComponentType::Movement));
        
        if(player != nullptr) {
            if(movement != nullptr) {
                //_dir = GetMoveDirection();
               // std::cout << _dir<< "\n";
                Vector3 direction = GetDirection();
                Vector3 right = Vector3(sin(direction.x - 3.14f/2.0f), 0, cos(direction.x - 3.14f/2.0f));
                
                Vector3 velocity = Vector3(0.0, 0.0, 0.0);
                if(_dir == 0) velocity += right;
                else if(_dir == 1) velocity -= right;
                else if(_dir == 2) velocity -= direction;
                else if(_dir == 3) velocity += direction;
                
                movement->SetVelocity(velocity);
            }
            
            auto cameraIt = player->GetAssignedGameObject()->GetChildsIterator();
            while(cameraIt != player->GetAssignedGameObject()->GetChildsIteratorEnd())
            {
                auto view = dynamic_cast<IView*>((*cameraIt)->GetComponent(EComponentType::View));
                
                if(view != nullptr) {
                    view->LookAt(GetDirection());
                }
                
                cameraIt++;
            }
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

Vector2 KeyboardManager::GetMouseOrientation()
{
    return _orientation;
}

Vector3 KeyboardManager::GetDirection()
{
    // Source: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
    return Vector3(cos(_orientation.y) * sin(_orientation.x), sin(_orientation.y), cos(_orientation.y) * cos(_orientation.x));
}
