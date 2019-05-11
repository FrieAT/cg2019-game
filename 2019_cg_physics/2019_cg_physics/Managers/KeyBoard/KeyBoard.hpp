//
//  KeyBoard.hpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 09.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef KeyBoard_hpp
#define KeyBoard_hpp

#include <stdio.h>

#endif /* KeyBoard_hpp */
#ifndef KeyboardManager_hpp
#define KeyboardManager_hpp

#include "AbstractManager.hpp"

class GLFWwindow;

class KeyboardManager : public AbstractManager
{
public:
    
    void Initialize() override;
    
    void Loop() override;
    
    KeyboardManager(const Game & engine);
    ~KeyboardManager() = default;
    
    static void keyCallback(GLFWwindow* myWindow, int key, int scanCode, int action, int mod) { } // TODO.
private:
    
};

#endif /* KeyboardManager_hpp */
