//
//  DefaultShader.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 25.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef DefaultShader_hpp
#define DefaultShader_hpp

#include "IShader.hpp"

class DefaultShader : public IShader
{
public:
    void Init();
    
    const char* GetShaderSource(EShaderType shader)
    {
        switch(shader)
        {
            case EShaderType::VertexShader:
                return _vertexShader.c_str();
            case EShaderType::FragmentShader:
                return _fragmentShader.c_str();
            default:
                return nullptr;
        }
    }
    
    const std::string GetShaderId()
    {
        return "DefaultShader";
    }
    
    DefaultShader();
    ~DefaultShader() = default;
private:
    std::string _vertexShader;
    std::string _fragmentShader;
};

#endif /* DefaultShader_hpp */
