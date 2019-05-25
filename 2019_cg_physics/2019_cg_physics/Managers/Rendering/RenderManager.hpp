#ifndef RenderManager_hpp
#define RenderManager_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "Game.hpp"
#include "AbstractManager.hpp"
#include "EShaderType.hpp"
#include "IView.hpp"

class RenderManager : public AbstractManager
{
public:
    void Initialize() override;
    void Loop() override;
    const IView* getCurrentCamera() {
        if(_currentCamera == nullptr) {
            return _currentCamera;
        }
        return const_cast<const IView*>(_currentCamera);
    }
    
    //TODO: Move to IView
    //TODO: Refactoring needed.
    int GetPositionAttrib() { return posAttrib; }
    int GetNormalAttrib() { return normAttrib; }
    int GetColorVtxAttrib() { return colAttrib; }
    int GetShininessAttrib() { return shininessAttrib; }
    
    RenderManager(const Game &engine);
    ~RenderManager() = default;
    
    const std::string UniformAnim = "anim";
private:
    GLint getUniformId(GLint shaderProgram, const char* uniformName);
    GLint getAttribId(GLint shaderProgram, const char* attributeName);
    GLuint getShaderIdByType(EShaderType shaderType);
    bool checkShaderCompileStatus(GLuint shaderID);
    bool checkShaderProgramLinkStatus(GLuint programID);
    
    IView* _currentCamera;
    std::map<std::string, unsigned int> _shaderPrograms;
    
    //TODO: Move to IView
    //TODO: Refactoring needed.
    int posAttrib;
    int normAttrib;
    int colAttrib;
    int shininessAttrib;
};

#endif /* RenderManager_hpp */
