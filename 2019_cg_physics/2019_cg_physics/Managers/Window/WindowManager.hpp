#ifndef WindowManager_hpp
#define WindowManager_hpp

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "AbstractManager.hpp"

class WindowManager : public AbstractManager
{
public:
    
    void Initialize() override;
    
    void Loop() override;
    
    GLFWwindow * GetWindow();
    
    WindowManager(const Game & engine);
    ~WindowManager() = default;
private:
    int windowWidth =1024;

    
    int windowHeight =768;
   
    
    const char* windowName = "The Game";
    
    GLFWwindow * _window;
    
    static void errorCallback(int error, const char*logText);
};

#endif /* WindowManager_hpp */
