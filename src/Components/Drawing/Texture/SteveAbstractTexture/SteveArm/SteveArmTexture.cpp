//
//  SteveArmTexture.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 11.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "SteveArmTexture.hpp"

SteveArmTexture::SteveArmTexture()
{
    _points = {
        // bottom
        0.8125f, 0.6875f,
        0.75f, 0.6875f,
        0.8125f, 0.75f,
        
        0.75f, 0.75f,
        0.75f, 0.6875f,
        0.8125f, 0.75f,
        
        // top
        0.75f, 0.6875f,
        0.6875f, 0.6875f,
        0.75f, 0.75f,
        
        0.6875f, 0.75f,
        0.6875f, 0.6875f,
        0.75f, 0.75f,
        
        // front
        0.6875f, 0.5f,
        0.75f, 0.5f,
        0.75f, 0.6875f,
        
        0.6875f, 0.5f,
        0.75f, 0.6875f,
        0.6875f, 0.6875f,
        
        // left
        0.6875f, 0.5f,
        0.6875f, 0.6875f,
        0.625f, 0.5f,
        
        0.625f, 0.5f,
        0.6875f, 0.6875f,
        0.625f, 0.6875f,
        
        // right
        0.75f, 0.5f,
        0.8125f, 0.5f,
        0.8125f, 0.6875f,
        
        0.75f, 0.5f,
        0.75f, 0.6875f,
        0.8125f, 0.6875f,
        
        // back
        0.8125f, 0.5f,
        0.875f, 0.5f, // rechts unten
        0.875f, 0.6875f,
        
        0.8125f, 0.5f,
        0.875f, 0.6875f,
        0.8125f, 0.6875f
    };
}
