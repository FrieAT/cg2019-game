//
//  GameOverBlockTexture.cpp
//  2019_cg_physics
//
//  Created by Masud Mostafa on 26.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "GameOverBlockTexture.hpp"

GameOverBlockTexture::GameOverBlockTexture()
{
    _points = {
        // bottom
        0.5f + 0.375f, 0.875f - 0.5f,
        0.5f + 0.25f, 0.875f - 0.5f,
        0.5f + 0.375f, 1.0f - 0.5f,
        
        0.5f +  0.25f, 1.0f - 0.5f,
        0.5f + 0.25f, 0.875f - 0.5f,
        0.5f + 0.375f, 1.0f - 0.5f,
        
        // top
        0.5f + 0.25f, 0.875f - 0.5f, // rechts unten
        0.5f + 0.125f, 0.875f - 0.5f, // links oben
        0.5f + 0.25f, 1.0f - 0.5f, // rechts oben
        
        0.5f + 0.125f, 1.0f - 0.5f,  // links oben
        0.5f + 0.125f, 0.875f - 0.5f, // links unten
        0.5f + 0.25f, 1.0f - 0.5f, // rechts unten
        
        // front
        0.5f + 0.125f, 0.75f - 0.5f, // links unten
        0.5f + 0.25f, 0.75f - 0.5f, // rechts unten
        0.5f + 0.25f, 0.875f - 0.5f, // rechts oben
        
        0.5f + 0.125f, 0.75f - 0.5f, // links unten
        0.5f + 0.25f, 0.875f - 0.5f, // rechts oben
        0.5f + 0.125f, 0.875f - 0.5f, // links oben
        
        // left
        0.5f + 0.125f, 0.75f - 0.5f,
        0.5f + 0.125f, 0.875f - 0.5f,
        0.5f + 0.0f, 0.75f - 0.5f,
        
        0.5f + 0.0f, 0.75f - 0.5f,
        0.5f + 0.125f, 0.875f - 0.5f,
        0.5f + 0.0f, 0.875f - 0.5f,
        
        // right
        0.5f + 0.25f, 0.75f - 0.5f,
        0.5f + 0.375f, 0.75f - 0.5f,
        0.5f + 0.375f, 0.875f - 0.5f,
        
        0.5f + 0.25f, 0.75f - 0.5f,
        0.5f + 0.25f, 0.875f - 0.5f,
        0.5f + 0.375f, 0.875f - 0.5f,
        
        // back
        0.5f + 0.375f, 0.75f - 0.5f,
        0.5f + 0.5f, 0.75f - 0.5f,
        0.5f + 0.5f, 0.875f - 0.5f,
        
        0.5f + 0.375f, 0.75f - 0.5f,
        0.5f + 0.5f, 0.875f - 0.5f,
        0.5f + 0.375f, 0.875f - 0.5f
    };
}
