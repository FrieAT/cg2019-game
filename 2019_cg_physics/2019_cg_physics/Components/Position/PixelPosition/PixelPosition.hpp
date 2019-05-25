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

class PixelPosition : public IPosition
{
public:
    PixelPosition();
    ~PixelPosition() = default;
    
    Vector3 GetPosition();
    void SetPosition(Vector3 setPosition);
    void AddPosition(Vector3 addPosition);
private:
    Vector3 _position;
};

#endif /* PixelPosition_hpp */
