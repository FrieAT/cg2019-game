//
//  LinearMovement.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 25.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef LinearMovement_hpp
#define LinearMovement_hpp

#include "IMovement.hpp"
#include "IPosition.hpp"

class LinearMovement : public IMovement
{
public:
    LinearMovement();
    void AddVelocity(Vector3 addVelocity) { _move = _move + addVelocity; }
    void SetVelocity(Vector3 velocity) { _move = velocity; }
    //
   
    Vector3 GetVelocity() { return _move; }
    void SetFriction(float friction) { return; };
    float GetFriction() { return 1.0f; }
    void SetSpeed(float speed) { _speed = speed; }
    float GetSpeed() { return _speed; }
private:
    
    Vector3 _move;
    float _speed;
};

#endif /* LinearMovement_hpp */
