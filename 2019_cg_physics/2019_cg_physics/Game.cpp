
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
#include "GameLogicManager.hpp"
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
    AddManager<GameLogicManager>();
    // Adding GameObjects below.
    
    
    //auto stage = PrimitiveObjects::CreateStageDummy();
    //GetManager<ObjectManager>()->AddGameObject(stage);

    auto triangle = PrimitiveObjects::CreateSteve();
    GetManager<ObjectManager>()->AddGameObject(triangle);
    
    // Adding GameObjects below.
    auto camera = PrimitiveObjects::CreateCamera();
    GetManager<ObjectManager>()->AddGameObject(camera);

    PrimitiveObjects::GenerateBallsForLevel(GetManager<ObjectManager>(), Vector3(0.0f), 2.0f, 5.0f);
    PrimitiveObjects::GenerateLandschaft(GetManager<ObjectManager>(), Vector3(0.0f, -0.25f, 0.0f), 7.0f, 4.0f);
    PrimitiveObjects::GenerateFenceAroundField(GetManager<ObjectManager>());

    this->initializeManagers();
   
    _initialized = true;
    
    double lastTime = 0;
    double currentTime;
    double maxFPS = 1.0 / 24.0;
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
