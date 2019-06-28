//
//  IAnimation.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 28.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef IAnimation_h
#define IAnimation_h

#include "IComponent.hpp"
#include "IPosition.hpp"

class IAnimation : public IComponent
{
public:
    IAnimation() = default;
    ~IAnimation() = default;
    
    virtual void SetInitialRotation(float rotation) = 0;
    virtual void SetForward(bool forward) = 0;
    virtual void AnimateByVelocity(Vector3 velocity, float deltaTime) = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Animation;
    }
private:
};

#endif /* IAnimation_h */
