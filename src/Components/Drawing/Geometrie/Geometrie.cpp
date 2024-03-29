//
//  Geometrie.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 04.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "Geometrie.hpp"

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "IShader.hpp"

Geometrie::~Geometrie()
{
    deleteBufferAndArray();
}

void Geometrie::Init()
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int posAttrib = shader->GetAttrib(EShaderAttrib::Position);
    //int normAttrib = shader->GetAttrib(EShaderAttrib::Normal);
    
    organize(posAttrib);
}

void Geometrie::Draw(RenderManager* renderManager)
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int colAttrib = shader->GetAttrib(EShaderAttrib::Color);
    int shininessAttrib = shader->GetUniform(EShaderUniform::Shininess);
    
    draw(colAttrib, shininessAttrib);
  
}
/* generate and organize buffers */
void Geometrie::organize(GLint posAttrib)
{
    GLfloat points[] = {

  
        // Front
      
      0.0f, 1.0f, 0.0f,
    
       -1.0f, -1.0f, 1.0f,
     
      1.0f, -1.0f, 1.0f,
        
        // Right
       
      0.0f, 1.0f, 0.0f,

        1.0f, -1.0f, 1.0f,
      
        1.0f, -1.0f, -1.0f,
        
        // Back
      
     0.0f, 1.0f, 0.0f,
      
        1.0f, -1.0f, -1.0f,
        
       -1.0f, -1.0f, -1.0f,
        
        // Left
      
    0.0f, 1.0f, 0.0f,
       
      -1.0f,-1.0f,-1.0f,
      
       -1.0f,-1.0f, 1.0f,
    };
    
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    /* copy the vertex data to it */
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}
void Geometrie::draw(GLint colAttrib, GLint shininessAttrib)
{
    glBindVertexArray(myVAO);
    
 
    
    glUniform1f(shininessAttrib,300);
    
    
    glVertexAttrib3f(colAttrib, 0.0f, 1.0f, 0.0f);
    /* draw the VAO */
    glDrawArrays(GL_TRIANGLES, 0, 12);
    
}
void Geometrie::deleteBufferAndArray()
{ glDeleteBuffers(1, &myVBO);
    glDeleteVertexArrays(1, &myVAO);
}



