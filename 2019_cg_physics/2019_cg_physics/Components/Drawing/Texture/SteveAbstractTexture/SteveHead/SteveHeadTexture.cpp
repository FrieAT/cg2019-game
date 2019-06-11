//
//  SteveHeadTexture.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "SteveHeadTexture.hpp"

SteveHeadTexture::SteveHeadTexture()
{
    _points = {
        // bottom
        0.375f, 0.875f,
        0.25f, 0.875f,
        0.375f, 1.0f,
        
        0.25f, 1.0f,
        0.25f, 0.875f,
        0.375f, 1.0f,
        
        // top
        0.25f, 0.875f,
        0.125f, 0.875f,
        0.25f, 1.0f,
        
        0.125f, 1.0f,
        0.125f, 0.875f,
        0.25f, 1.0f,
        
        // front
        0.125f, 0.75f,
        0.25f, 0.75f,
        0.25f, 0.875f,
        
        0.125f, 0.75f,
        0.25f, 0.875f,
        0.125f, 0.875f,
        
        // left
        0.125f, 0.75f,
        0.125f, 0.875f,
        0.0f, 0.75f,
        
        0.0f, 0.75f,
        0.125f, 0.875f,
        0.0f, 0.875f,
        
        // right
        0.25f, 0.75f,
        0.375f, 0.75f,
        0.375f, 0.875f,
        
        0.25f, 0.75f,
        0.25f, 0.875f,
        0.375f, 0.875f,
        
        // back
        0.375f, 0.75f,
        0.5f, 0.75f,
        0.5f, 0.875f,
        
        0.375f, 0.75f,
        0.5f, 0.875f,
        0.375f, 0.875f
    };
}
