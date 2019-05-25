//
//  DefaultShader.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 25.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "DefaultShader.hpp"

DefaultShader::DefaultShader()
{
    _vertexShader = GLSL(
    in vec3 positionIn;
    void main() {
        gl_Position = vec4(positionIn, 1.0);
    }
    );
    
    _fragmentShader = GLSL(
        out vec4 outColor;
        void main() {
            outColor = vec4(0.5, 0.0, 0.5, 1.0);
        }
    );
}

void DefaultShader::Init()
{
    
}
