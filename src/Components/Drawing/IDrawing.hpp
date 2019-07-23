#ifndef IDrawing_h
#define IDrawing_h

#include "IComponent.hpp"
#include "ITexture.hpp"

class RenderManager;

class IDrawing : public IComponent
{
public:
    
    virtual void Draw(RenderManager* renderManager) = 0;
    
    virtual void SetTexture(ITexture * newTexture)
    {
        _texture = newTexture;
    }
    virtual ITexture* GetTexture()
    {
        return _texture;
    }
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Drawing;
    }
protected:
    ITexture* _texture = nullptr;
};

#endif /* IDrawing_h */
