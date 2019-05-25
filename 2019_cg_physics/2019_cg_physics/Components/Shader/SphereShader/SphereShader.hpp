//
//  SphereShader.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 17.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef SphereShader_hpp
#define SphereShader_hpp

#include "IShader.hpp"

class SphereShader : public IShader
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
        return "SphereShader";
    }
    
    SphereShader();
    ~SphereShader() = default;
private:
    std::string _vertexShader;
    std::string _fragmentShader;
};

#endif /* SphereShader_hpp */
