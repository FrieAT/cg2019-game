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
