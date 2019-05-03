//
//  RenderManager.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef RenderManager_hpp
#define RenderManager_hpp

#include <stdio.h>

#include "Game.hpp"
#include "AbstractManager.hpp"

class RenderManager : public AbstractManager
{
public:
    void Initialize() override;
    void Loop() override;
    
    RenderManager(const Game &engine);
    ~RenderManager() = default;
private:
    
};

#endif /* RenderManager_hpp */
