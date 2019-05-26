
#include <chrono>
#include <thread>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "Game.hpp"

#include "RenderManager.hpp"
#include "WindowManager.hpp"
#include "ObjectManager.hpp"
#include "KeyboardManager.hpp"
#include "PrimitiveObjects.hpp"
#include "KeyboardManager.hpp"
#include "PhysicsManager.hpp"
#include "SphereDrawing.hpp"
SphereDrawing sphereDrawing;
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
    AddManager<PhysicsManager>();
    // Adding GameObjects below.
    
    
    auto stage = PrimitiveObjects::CreateStageDummy();
    GetManager<ObjectManager>()->AddGameObject(stage);
  
    
    auto triangle = PrimitiveObjects::CreateCubeDummy();
    GetManager<ObjectManager>()->AddGameObject(triangle);
    
    // Adding GameObjects below.
    auto camera = PrimitiveObjects::CreateCamera();
    GetManager<ObjectManager>()->AddGameObject(camera);
    for(int i = 0; i < 3; i++) {
        auto spfhere = PrimitiveObjects::CreateSphereDummy();
        GetManager<ObjectManager>()->AddGameObject(spfhere);
    
    
    }

    

    this->initializeManagers();
   
    _initialized = true;
    
    
    double lastTime = 0;
    double currentTime;
    double maxFPS = 1.0 / 50.0; // limiting FPS to 50 - 65 FPS!
    // Run the loop.
    while(!this->_shutdown) // TODO: Check for Keyboard Interrupt!
    {
        currentTime = glfwGetTime();
        _deltaTime = currentTime - lastTime;
        lastTime = currentTime;
   
        this->loopManagers();
        
        if(maxFPS >= _deltaTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds((long)((maxFPS - _deltaTime) * 1000.0)));
        }
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
