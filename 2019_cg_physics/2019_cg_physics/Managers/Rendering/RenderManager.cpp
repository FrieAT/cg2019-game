#include "RenderManager.hpp"
#include "WindowManager.hpp"
#include "ObjectManager.hpp"
#include "IDrawing.hpp"

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
    auto objectManager = this->GetEngine().GetManager<ObjectManager>();
    
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //TODO: Drawing.
    auto objects = objectManager->GetObjectsByName("test");
    auto it = objects.begin();
    while(it != objects.end())
    {
        auto drawing = dynamic_cast<IDrawing*>((*it)->GetComponent(EComponentType::Drawing));
        if(drawing != nullptr)
        {
            drawing->Draw();
        }
        it++;
    }
    
    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(windowManager->GetWindow());
}
