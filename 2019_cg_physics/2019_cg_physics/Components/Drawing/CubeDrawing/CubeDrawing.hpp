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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLSL(src) "#version 330 core\n" #src
#include <iostream>
#include <stdio.h>


class CubeDrawing : public IDrawing
{
public:
    CubeDrawing() = default;
    ~CubeDrawing();
    void Init();
    void Draw(RenderManager* renderManager);
    void organize(GLint posAttrib);
    void draw(GLint colAttrib, GLint shininessAttrib);
    void deleteBufferAndArray();
  
private:
    float colorValues[3] = { 0 };
    const GLfloat SPEED=0.5;
    GLuint myVAO;
    GLuint myVBO;
    glm::mat4 animPlayer= glm::mat4(1.0f);
    glm::mat4  anim= glm::mat4(1.0f);
    GLfloat curTrans [3] = { 0.0f, 0.0f, 0.0f };
    
    const GLfloat STAGE_AREA_LENGTH_HALF = 2.5f;
    const GLfloat STAGE_AREA_WIDTH_HALF = 1.0f;
    const GLfloat STAGE_AREA_WIDTH_HALF_BOTTOM = 2.0f;
};

#endif /* CubeDrawing_hpp */
