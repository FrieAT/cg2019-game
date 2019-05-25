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
#include "EShaderAttrib.hpp"
#include "EShaderUniform.hpp"

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
    
    virtual bool IsCompiledAndLinked()
    {
        return (_shaderProgram == 0 ? false : true);
    }
    
    virtual int GetAttrib(EShaderAttrib attribute)
    {
        auto it = _attribHandler.find(attribute);
        if(it != _attribHandler.end()) {
            return (*it).second;
        }
        return -1;
    }
    
    virtual void AddAttrib(EShaderAttrib attribute, int handler)
    {
        auto it = _attribHandler.find(attribute);
        if(it == _attribHandler.end()) {
            _attribHandler.insert(std::pair<EShaderAttrib, int>(attribute, handler));
            return;
        }
        throw std::exception();
    }
    
    virtual int GetUniform(EShaderUniform uniforme)
    {
        auto it = _uniformHandler.find(uniforme);
        if(it != _uniformHandler.end()) {
            return (*it).second;
        }
        return -1;
    }
    
    virtual void AddUniform(EShaderUniform uniforme, int handler)
    {
        auto it = _uniformHandler.find(uniforme);
        if(it == _uniformHandler.end()) {
            _uniformHandler.insert(std::pair<EShaderUniform, int>(uniforme, handler));
            return;
        }
        throw std::exception();
    }
    
    static const char* AttribStr(EShaderAttrib attribType) {
        switch(attribType)
        {
            case EShaderAttrib::Position:
                return "positionIn";
            case EShaderAttrib::Normal:
                return "normalIn";
            case EShaderAttrib::Color:
                return "colorVtxIn";
            default:
                throw std::exception();
        }
    }
    
    static const char* UniformStr(EShaderUniform uniformType) {
        switch(uniformType)
        {
            case EShaderUniform::CameraPosition:
                return "cameraPosition";
            case EShaderUniform::CameraView:
                return "view";
            case EShaderUniform::CameraProjection:
                return "proj";
            case EShaderUniform::Shininess:
                return "shininess";
            case EShaderUniform::Model:
                return "anim";
            default:
                throw std::exception();
        }
    }
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Shader;
    }
protected:
    unsigned int _shaderProgram = 0;
    std::map<EShaderAttrib, int> _attribHandler;
    std::map<EShaderUniform, int> _uniformHandler;
};

#endif /* IShader_h */
