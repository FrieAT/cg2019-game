//
//  PixelPosition.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 11.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "PixelPosition.hpp"

PixelPosition::PixelPosition()
: _position(Vector3(0.0, 0.0, 0.0))
{
}

Vector3 PixelPosition::GetPosition()
{
    return _position;
}

void PixelPosition::SetPosition(Vector3 setPosition)
{
    _position = setPosition;
}

void PixelPosition::AddPosition(Vector3 addPosition)
{
    _position += addPosition;
}


