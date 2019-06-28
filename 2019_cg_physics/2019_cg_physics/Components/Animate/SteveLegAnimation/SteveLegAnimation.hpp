//
//  SteveLegAnimation.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 28.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef SteveLegAnimation_hpp
#define SteveLegAnimation_hpp

#include "IAnimation.hpp"

class SteveLegAnimation : public IAnimation
{
public:
    void SetInitialRotation(float rotation) { _oldRotation = rotation; }
    void SetForward(bool forward) { _forward = forward; }
    void AnimateByVelocity(Vector3 velocity, float deltaTime);
private:
    bool _forward = true;
    float _oldRotation = 0.0f;
};

#endif /* SteveLegAnimation_hpp */
