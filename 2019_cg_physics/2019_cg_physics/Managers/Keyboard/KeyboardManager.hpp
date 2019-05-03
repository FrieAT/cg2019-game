
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
