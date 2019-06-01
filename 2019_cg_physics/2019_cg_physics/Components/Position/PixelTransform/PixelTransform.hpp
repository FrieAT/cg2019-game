//
//  PixelPosition.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 11.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef PixelPosition_hpp
#define PixelPosition_hpp

#include "IPosition.hpp"

class PixelTransform : public IPosition
{
public:
    PixelTransform();
    ~PixelTransform() = default;
    
    Vector3 GetPosition();
    void SetPosition(Vector3 setPosition);
    void AddPosition(Vector3 addPosition);
    
    Vector3 GetScale();
    void SetScale(Vector3 setScale);
    
    Vector3 GetRotation();
    void SetRotation(Vector3 setRotation);
private:
    Vector3 _position;
    Vector3 _scale;
    Vector3 _rotation;
};

#endif /* PixelPosition_hpp */
