//
//  SteveArmAnimation.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 28.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "SteveArmAnimation.hpp"

#include "IPosition.hpp"

void SteveArmAnimation::AnimateByVelocity(Vector3 velocity, float deltaTime)
{
    auto position = dynamic_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    if(position != nullptr) {
        float newRotation;
        float speed = 2.5f + glm::length(velocity);
        
        if(glm::length(velocity) > 0.0f) {
            if(_forward) {
                newRotation = 30.0f;
            } else {
                newRotation = -30.0f;
            }
            
            if(abs(newRotation - _oldRotation) < 2.5f) {
                _forward = !_forward;
            }
        } else {
            newRotation = 0.0f;
        }
        
        float setRotationTo = _oldRotation + (newRotation - _oldRotation) * deltaTime * speed;
        position->SetRotation(ERotation::Yaw, setRotationTo);
        _oldRotation = setRotationTo;
    }
}
