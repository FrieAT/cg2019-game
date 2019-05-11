#ifndef DummyTriangleDrawing_hpp
#define DummyTriangleDrawing_hpp

#include "IDrawing.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLSL(src) "#version 330 core\n" #src

class DummyTriangleDrawing : public IDrawing
{
public:
    void Draw();
  

    GLuint shaderProgram ;
    int dir;
    glm::mat4  anim = glm::mat4(1.0f);
      const char* uniformName;

private:
      float colorValues[3] = { 0 };
    const GLfloat SPEED=0.5; 
  
};

#endif /* DummyTriangleDrawing_hpp */
