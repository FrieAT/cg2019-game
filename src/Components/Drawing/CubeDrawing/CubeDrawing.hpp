//
//  CubeDrawing.hpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 12.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef CubeDrawing_hpp
#define CubeDrawing_hpp

#include <stdio.h>

#include "IDrawing.hpp"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <stdio.h>


class CubeDrawing : public IDrawing
{
public:
    CubeDrawing() = default;
    ~CubeDrawing();
    void Init();
    void Draw(RenderManager* renderManager);
   
    void organize(GLint posAttrib, GLint uvAttrib, GLint normAttrib);
    void draw(GLint colAttrib, GLint shininessAttrib, GLint enableTextureUniform);
    void deleteBufferAndArray();
  
private:
    GLuint myVAO;
    GLuint myVBO;
};

#endif /* CubeDrawing_hpp */
