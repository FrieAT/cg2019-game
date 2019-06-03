//
//  PixelPosition.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 11.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include <glm/gtx/euler_angles.hpp>

#include "PixelTransform.hpp"

PixelTransform::PixelTransform()
: _position(Vector3(0.0f, 0.0f, 0.0f))
, _scale(Vector3(1.0f, 1.0f, 1.0f))
, _rotation(Matrix4(1.0f))
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

Matrix4 PixelTransform::GetRotation()
{
    return _rotation;
}

void PixelTransform::SetRotation(ERotation type, float degreeRotation)
{
    Vector3 vecRotate;
    switch(type)
    {
        case ERotation::Yaw:
            vecRotate = Vector4(1.0, 0.0, 0.0, 1.0f);
            break;
        case ERotation::Pitch:
            vecRotate = Vector4(0.0, 1.0, 0.0, 1.0f);
            break;
        case ERotation::Roll:
            vecRotate = Vector4(0.0, 0.0, 1.0, 1.0f);
            break;
    }
    _rotation = _rotation * glm::rotate(Matrix4(1.0f), glm::radians(degreeRotation), vecRotate);
}

