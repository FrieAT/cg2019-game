//
//  IShader.h
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 17.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef IShader_h
#define IShader_h

#define GLSL(src) "#version 330 core\n" #src

#include <map>

#include "IComponent.hpp"
#include "EShaderType.hpp"

class IShader : public IComponent
{
public:
    virtual const char* GetShaderSource(EShaderType shader) = 0;
    
    virtual void SetShaderProgram(unsigned int shaderProgramId)
    {
        _shaderProgram = shaderProgramId;
    }
    
    virtual unsigned int GetShaderProgram()
    {
        return _shaderProgram;
    }
    
    virtual const std::string GetShaderId() = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Shader;
    }
protected:
    unsigned int _shaderProgram;
};

#endif /* IShader_h */
