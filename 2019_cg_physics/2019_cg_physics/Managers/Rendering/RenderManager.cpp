#include "RenderManager.hpp"
#include "WindowManager.hpp"

RenderManager::RenderManager(const Game &engine)
: AbstractManager(engine)
{
    
}

void RenderManager::Initialize()
{
    
}

void RenderManager::Loop()
{
    auto windowManager = this->GetEngine().GetManager<WindowManager>();
    
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //TODO: Drawing.
    
    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(windowManager->GetWindow());
}
