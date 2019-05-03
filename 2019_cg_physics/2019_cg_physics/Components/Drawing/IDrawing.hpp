#ifndef IDrawing_h
#define IDrawing_h

#include "IComponent.hpp"

class IDrawing : public IComponent
{
public:
    
    virtual void Draw() = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Drawing;
    }
private:
    
};

#endif /* IDrawing_h */
