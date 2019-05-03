

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.hpp"

#include "WindowManager.hpp"

#include "KeyboardManager.hpp"

KeyboardManager::KeyboardManager(const Game & engine)
: AbstractManager(engine)
{
    
}

void KeyboardManager::Initialize()
{
    auto windowManager = GetEngine().GetManager<WindowManager>();
    
    auto window = windowManager->GetWindow();
    
    glfwSetKeyCallback(window, KeyboardManager::keyCallback);
}

void KeyboardManager::Loop()
{

}
