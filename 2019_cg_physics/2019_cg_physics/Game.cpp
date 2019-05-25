#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "Game.hpp"

#include "RenderManager.hpp"
#include "WindowManager.hpp"
#include "ObjectManager.hpp"
#include "KeyboardManager.hpp"
#include "PrimitiveObjects.hpp"
#include "KeyboardManager.hpp"

Game* Game::_engine = nullptr;

Game::Game()
: _shutdown(false)
{
}

void Game::Initialize()
{
    if(_engine != nullptr) {
        throw std::exception();
    }
    _engine = this;
    
    // Adding Managers below.
    AddManager<WindowManager>();
    AddManager<KeyboardManager>();
    AddManager<RenderManager>();
    AddManager<ObjectManager>();
    
    // Adding GameObjects below.
    auto camera = PrimitiveObjects::CreateCamera();
    GetManager<ObjectManager>()->AddGameObject(camera);
    /*
    auto stage = PrimitiveObjects::CreateStageDummy();
    GetManager<ObjectManager>()->AddGameObject(stage);
    // Adding GameObjects below.
    //auto cube = PrimitiveObjects::CreateCubeDummy();
    //GetManager<ObjectManager>()->AddGameObject(cube);
    */
    auto triangle = PrimitiveObjects::CreateTriangleDummy();
    GetManager<ObjectManager>()->AddGameObject(triangle);
    
    // Adding GameObjects below.
    auto spfhere = PrimitiveObjects::CreateSphereDummy();
    GetManager<ObjectManager>()->AddGameObject(spfhere);
    /*
    auto spfhere1 = PrimitiveObjects::CreateSphereDummy();
     GetManager<ObjectManager>()->AddGameObject(spfhere1);
    auto spfhere2 = PrimitiveObjects::CreateSphereDummy();
    GetManager<ObjectManager>()->AddGameObject(spfhere2);
    */
  
    // Initialize Managers below.
    this->initializeManagers();
    
    _initialized = true;
    
    // Run the loop.
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
