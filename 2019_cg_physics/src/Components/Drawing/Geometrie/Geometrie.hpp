//
//  Geometrie.hpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 04.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef Geometrie_hpp
#define Geometrie_hpp

#include <stdio.h>
#include <stdio.h>

#include "IDrawing.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLSL(src) "#version 330 core\n" #src
#include <iostream>
#include <stdio.h>


class Geometrie : public IDrawing
{
public:
    Geometrie() = default;
    ~Geometrie();
    void Init();
    void Draw(RenderManager* renderManager);
  
    void organize(GLint posAttrib);
    void draw(RenderManager* renderManager);
    void deleteBufferAndArray();
      void draw(GLint colAttrib, GLint shininessAttrib);
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
#endif /* Geometrie_hpp */
