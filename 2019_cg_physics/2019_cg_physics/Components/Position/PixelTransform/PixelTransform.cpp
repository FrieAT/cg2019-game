//
//  PixelPosition.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 11.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "PixelTransform.hpp"

PixelTransform::PixelTransform()
: _position(Vector3(0.0, 0.0, 0.0))
, _scale(Vector3(1.0, 1.0, 1.0))
, _rotation(Vector3(0.0, 0.0, 0.0))
{
}

Vector3 PixelTransform::GetPosition()
{
    return _position;
}

void PixelTransform::SetPosition(Vector3 setPosition)
{
    _position = setPosition;
}

void PixelTransform::AddPosition(Vector3 addPosition)
{
    _position += addPosition;
}

Vector3 PixelTransform::GetScale()
{
    return _scale;
}

void PixelTransform::SetScale(Vector3 setScale)
{
    _scale = setScale;
}

Vector3 PixelTransform::GetRotation()
{
    return _rotation;
}

void PixelTransform::SetRotation(Vector3 setRotation)
{
    _rotation = setRotation;
}

