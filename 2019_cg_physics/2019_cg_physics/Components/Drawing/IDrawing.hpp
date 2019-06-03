#ifndef IDrawing_h
#define IDrawing_h

#include "IComponent.hpp"

class RenderManager;

class IDrawing : public IComponent
{
public:
    
    virtual void Draw(RenderManager* renderManager) = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Drawing;
    }
private:
    
};

#endif /* IDrawing_h */
