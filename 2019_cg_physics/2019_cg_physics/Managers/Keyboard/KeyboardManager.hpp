
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
    
    static int GetMoveDirection() { return _dir; }
    
    static void keyCallbackM(GLFWwindow* myWindow, int key, int scanCode, int action, int mod); // TODO.
private:
    static int _dir;
};

#endif /* KeyboardManager_hpp */
