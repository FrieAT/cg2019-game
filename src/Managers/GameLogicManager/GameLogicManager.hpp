//
//  GameLogicManager.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 28.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef GameLogicManager_hpp
#define GameLogicManager_hpp

#include "AbstractManager.hpp"

class GameLogicManager : public AbstractManager
{
public:
    void Initialize();
    void Loop();
    
    GameLogicManager(const Game &engine);
private:
    float _remainingGameTime = 3.0f * 60.0f;
    float _maxGameTime = 3.0f * 60.0f;
    bool _gameOver = false;
};

#endif /* GameLogicManager_hpp */
