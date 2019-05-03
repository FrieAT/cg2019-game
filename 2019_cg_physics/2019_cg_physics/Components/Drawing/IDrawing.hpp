//
//  IDrawing.h
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

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
