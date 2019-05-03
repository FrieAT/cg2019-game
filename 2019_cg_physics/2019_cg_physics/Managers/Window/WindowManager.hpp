//
//  WindowManager.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 23.04.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef WindowManager_hpp
#define WindowManager_hpp

#include "AbstractManager.hpp"

class WindowManager : public AbstractManager
{
public:
    
    void Initialize() override;
    
    void Loop() override;
    
    const GLFWwindow * GetWindow() const();
    
    WindowManager(const Game & engine);
    ~WindowManager() = default;
private:
    int windowWidth = 1024;
    
    int windowHeight = 768;
    
    const char* windowName = "The Game";
    
    GLFWwindow * _window;
    
    GLuint _defaultShaderPrograms;
    
    static void errorCallback(int error, const char*logText);
};

#endif /* WindowManager_hpp */
