//
//  Game.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 23.04.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "Game.hpp"

#include "RenderManager.hpp"
#include "WindowManager.hpp"
#include "ObjectManager.hpp"

Game::Game()
{
}

void Game::Initialize()
{
    AddManager<RenderManager>();
    AddManager<WindowManager>();
    AddManager<ObjectManager>();
    
    this->initializeManagers();
    
    while(true) // TODO: Check for Keyboard Interrupt!
    {
        this->loopManagers();
    }
}

void Game::initializeManagers()
{
    auto it = _managers.begin();
    while(it != _managers.end())
    {
        (*it)->Initialize();
        it++;
    }
}

void Game::loopManagers()
{
    auto it = _managers.begin();
    while(it != _managers.end())
    {
        (*it)->Loop();
        it++;
    }
}
