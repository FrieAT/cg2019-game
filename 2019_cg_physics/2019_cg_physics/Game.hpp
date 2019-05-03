//
//  Game.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 23.04.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>

#include "AbstractManager.hpp"
#include "Exception.hpp"

class Game
{
public:
    Game();
    ~Game() = default;
    
    void Initialize();
    
    template<typename T>
    void AddManager()
    {
        if(typeid(T) != typeid(AbstractManager))
        {
            //todo: throw Exception("Manager must be inherited from AbstractManager");
        }
        T * manager = new T(*this);
        _managers.push_back(manager);
    }
    
    template<typename T>
    const T * GetManager()
    {
        auto it = _managers.begin();
        while(it != _managers.end())
        {
            if(typeid(*it) == typeid(T))
            {
                return *it;
            }
            it++;
        }
        return nullptr;
    }
private:
    void initializeManagers();
    void loopManagers();
    
    std::vector<AbstractManager *> _managers;
};

#endif /* Game_hpp */
