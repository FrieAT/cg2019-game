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

class GLFWwindow;

class KeyboardManager : public AbstractManager
{
public:
    
    void Initialize() override;
    
    void Loop() override;
 
    KeyboardManager();
    KeyboardManager(const Game & engine);
    ~KeyboardManager() = default;
    
    static int GetMoveDirection() { return _dir; }
       int getHilf();
    static void keyCallbackM(GLFWwindow* myWindow, int key, int scanCode, int action, int mod); // TODO.
//private:
    static int _dir;
    int hilf= 0 ;
};

#endif /* KeyboardManager_hpp */
