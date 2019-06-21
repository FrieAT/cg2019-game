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

class GLFWwindow;

class KeyboardManager : public AbstractManager
{
public:
    
    void Initialize() override;
    
    void Loop() override;
    
    KeyboardManager(const Game & engine);
    ~KeyboardManager() = default;
    
    static int GetMoveDirection() { return _dir; }
    Vector2 GetMouseOrientation();
    Vector3 GetDirection();
    
    static void keyCallbackM(GLFWwindow* myWindow, int key, int scanCode, int action, int mod); // TODO.
private:
    static int _dir;
    Vector2 _orientation;
    float _mouseSpeedOrientation;
};

#endif /* KeyboardManager_hpp */
