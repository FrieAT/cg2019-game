#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "Game.hpp"

#include "RenderManager.hpp"
#include "WindowManager.hpp"
#include "ObjectManager.hpp"
#include "PrimitiveObjects.hpp"

Game::Game()
: _shutdown(false)
{
}

void Game::Initialize()
{
    // Adding Managers below.
    AddManager<RenderManager>();
    AddManager<WindowManager>();
    AddManager<ObjectManager>();
    
    // Adding GameObjects below.
    
    this->initializeManagers();
    
    while(!this->_shutdown) // TODO: Check for Keyboard Interrupt!
    {
        this->loopManagers();
    }
}

void Game::Shutdown()
{
    this->_shutdown = true;
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
