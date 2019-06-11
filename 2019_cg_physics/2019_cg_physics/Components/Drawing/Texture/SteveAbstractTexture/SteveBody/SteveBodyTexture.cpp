//
//  SteveHeadTexture.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "SteveBodyTexture.hpp"

SteveBodyTexture::SteveBodyTexture()
{
    _points = {
        // bottom
        0.5625f, 0.6875f,
        0.4375f, 0.6875f,
        0.5625f, 0.75f,
        
        0.4375f, 0.75f,
        0.4375f, 0.6875f,
        0.5625f, 0.75f,
        
        // top
        0.4375f, 0.6875f,
        0.3125f, 0.6875f,
        0.4375f, 0.75f,
        
        0.3125f, 0.75f,
        0.3125f, 0.6875f,
        0.4375f, 0.75f,
        
        // front
        0.3125f, 0.5f,
        0.4375f, 0.5f,
        0.4375f, 0.6875f,
        
        0.3125f, 0.5f,
        0.4375f, 0.6875f,
        0.3125f, 0.6875f,
        
        // left
        0.3125f, 0.5f,
        0.3125f, 0.6875f,
        0.25f, 0.5f,
        
        0.25f, 0.5f,
        0.3125f, 0.6875f,
        0.25f, 0.6875f,
        
        // right
        0.4375f, 0.5f,
        0.5f, 0.5f,
        0.5f, 0.6875f,
        
        0.4375f, 0.5f,
        0.4375f, 0.6875f,
        0.5f, 0.6875f,
        
        // back
        0.5f, 0.5f,
        0.625f, 0.5f,
        0.625f, 0.6875f,
        
        0.5f, 0.5f,
        0.625f, 0.6875f,
        0.5f, 0.6875f
    };
}
