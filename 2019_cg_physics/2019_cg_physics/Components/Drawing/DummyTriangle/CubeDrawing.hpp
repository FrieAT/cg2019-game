#ifndef CubeDrawing_hpp
#define CubeDrawing_hpp

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
    void Draw();
    void organize(GLint posAttrib);

    GLuint shaderProgram ;
    int dir;
    
      const char* uniformName;
     GLfloat curTrans [3] = { 0.0f, 0.0f, 0.0f };

    const GLfloat STAGE_AREA_LENGTH_HALF = 2.5f;
    const GLfloat STAGE_AREA_WIDTH_HALF = 1.0f;
  const GLfloat STAGE_AREA_WIDTH_HALF_BOTTOM = 2.0f;
private:
      float colorValues[3] = { 0 };
      const GLfloat SPEED=0.5;
      GLuint myVAO;
      GLuint myVBO;
glm::mat4  anim;
    glm::mat4 animPlayer;
      
  
};

#endif /* CubeDrawing_hpp */
