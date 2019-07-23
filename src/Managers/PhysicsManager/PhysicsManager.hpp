//
//  PhysicsManager.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 25.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef PhysicsManager_hpp
#define PhysicsManager_hpp

#include "AbstractManager.hpp"

class PhysicsManager : public AbstractManager
{
public:
    void Initialize();
    void Loop();
    void SetGravity(float gravity) { _gravity = gravity; }
    float GetGravity() { return _gravity; }
   
    PhysicsManager(const Game &engine);
private:
    float _gravity = 8.34;
    float _oldRotation = 0;
};

#endif /* PhysicsManager_hpp */
