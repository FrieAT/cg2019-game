//
//  KeyBoardManager.hpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 09.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef KeyboardManager_hpp
#define KeyboardManager_hpp

#include "AbstractManager.hpp"
#include "IPosition.hpp"

class KeyboardManager : public AbstractManager
{
public:
    
    void Initialize() override;
    
    void Loop() override;
    
    KeyboardManager(const Game & engine);
    ~KeyboardManager() = default;
    
    static Vector2 GetMoveDirection() { return _dir; }
    
    static void keyCallbackM(GLFWwindow* myWindow, int key, int scanCode, int action, int mod); // TODO.
private:
    static Vector2 _dir;
};

#endif /* KeyboardManager_hpp */
