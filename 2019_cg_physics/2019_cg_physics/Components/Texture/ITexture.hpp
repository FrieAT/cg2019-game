//
//  ITexture.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef ITexture_h
#define ITexture_h

#include "IComponent.hpp"

class ITexture : public IComponent
{
public:
    virtual void Texture() = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Texture;
    }
private:
    
};

#endif /* ITexture_h */
