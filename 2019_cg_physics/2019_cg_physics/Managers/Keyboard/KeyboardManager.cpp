

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.hpp"

#include "WindowManager.hpp"

#include "KeyboardManager.hpp"

int KeyboardManager::_dir;

KeyboardManager::KeyboardManager(const Game & engine)
: AbstractManager(engine)
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

}

void KeyboardManager:: keyCallbackM(GLFWwindow* myWindow, int key, int scanCode, int action, int mod)
{
    if (((key == GLFW_KEY_ESCAPE) || (key == GLFW_KEY_Q))  &&
        (action == GLFW_PRESS))
    /* close window upon hitting the escape key or Q/q */
        glfwSetWindowShouldClose(myWindow, GL_TRUE);
    else if ((key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS)) {
        _dir = 0;
    } else if ((key == GLFW_KEY_LEFT) && (action == GLFW_PRESS)) {
        _dir = 1;
    } else if ((key == GLFW_KEY_DOWN) && (action == GLFW_PRESS)) {
        _dir = 2;
    } else if ((key == GLFW_KEY_UP) && (action == GLFW_PRESS)) {
        _dir = 3;
    } else {
        _dir = -1;
    }
}
