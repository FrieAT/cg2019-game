//
//  AbstractManager.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef AbstractManager_hpp
#define AbstractManager_hpp

class Game;

class AbstractManager
{
public:
    AbstractManager(const Game &engine);
    
    virtual void Initialize() { }
    virtual void Loop() { }
private:
    const Game &_engine;
};

#endif /* AbstractManager_hpp */
