//
//  IPlayer.h
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 25.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef IPlayer_h
#define IPlayer_h

#include "IComponent.hpp"

class IPlayer : public IComponent
{
public:
    IPlayer() = default;
    ~IPlayer() = default;
    
    void SetPlayerId(unsigned int pId) { _playerId = pId; }
    unsigned int GetPlayerId() { return _playerId; }
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Player;
    }
private:
    unsigned int _playerId = 1;
};

#endif /* IPlayer_h */
