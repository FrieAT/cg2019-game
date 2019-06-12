//
//  IMovement.h
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 25.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef IMovement_h
#define IMovement_h

#include "IComponent.hpp"
#include "IPosition.hpp"

class IMovement : public IComponent
{
public:
    
    virtual void AddVelocity(Vector3 addVelocity) = 0;
    virtual void SetVelocity(Vector3 velocity) = 0;
    virtual Vector3 GetVelocity() = 0;
   
    virtual void SetFriction(float friction) = 0;
    virtual float GetFriction() = 0;
    virtual void SetSpeed(float speed) = 0;
    virtual float GetSpeed() = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Movement;
    }
private:
    
};

#endif /* IMovement_h */
