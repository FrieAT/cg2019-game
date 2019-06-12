//
//  PixelPosition.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 11.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef PixelTransform_hpp
#define PixelTransform_hpp

#include "IPosition.hpp"

class PixelTransform : public IPosition
{
public:
    PixelTransform();
    ~PixelTransform() = default;
    
    Vector3 GetPosition();
    void SetPosition(Vector3 setPosition);
    int GetHilf();
    void SetHilf(int setHilf);
    void AddPosition(Vector3 addPosition);
    
    Vector3 GetScale();
    void SetScale(Vector3 setScale);
    
    Matrix4 GetRotation();
    void SetRotation(ERotation type, float degreeRotation);
    void AddRotation(ERotation type, float degreeRotation);
private:
    Vector3 _position;
    Vector3 _scale;
    Matrix4 _rotation;
    int _hilf;
};

#endif /* PixelTransform_hpp */
