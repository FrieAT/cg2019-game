//
//  LineDrawing.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 11.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "LineDrawing.hpp"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IShader.hpp"

LineDrawing::~LineDrawing()
{
    deleteBufferAndArray();
}

void LineDrawing::Init()
{
   
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int posAttrib = shader->GetAttrib(EShaderAttrib::Position);
    int normAttrib = shader->GetAttrib(EShaderAttrib::Normal);
    
    organize(posAttrib);
}

void LineDrawing::Draw(RenderManager* renderManager)
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int colAttrib = shader->GetAttrib(EShaderAttrib::Color);
    int shininessAttrib = shader->GetUniform(EShaderUniform::Shininess);
    
    draw(colAttrib, shininessAttrib);
    // glBindVertexArray(0);
}
/* generate and organize buffers */
void LineDrawing::organize(GLint posAttrib)
{
//    GLfloat points[] = {
//
//        2.0f, 1.0f, 0,
//        1.0f, 2.0f, 0
//    };
//
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    /* copy the vertex data to it */
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}
void LineDrawing::draw(GLint colAttrib, GLint shininessAttrib)
{
    glBindVertexArray(myVAO);
    
    //    auto position = dynamic_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    //    position->SetPosition(Vector3(curTrans[0], curTrans[1], curTrans[2]));
    
    glUniform1f(shininessAttrib,300);
    
    
   glVertexAttrib3f(colAttrib, 1.0f, 1.0f, 1.0f);
    /* draw the VAO */
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_LINE_STIPPLE );
    glPushAttrib( GL_LINE_BIT );
    glLineWidth( 20.0f );
    glLineStipple(1, 0x00FF );
   // glLineStipple(1, 0x0101);
   
   // glLineStipple(1,0x1C47);
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, points );
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState( GL_VERTEX_ARRAY );
    glPopAttrib( );
    glDisable( GL_LINE_STIPPLE );
   glDisable( GL_LINE_SMOOTH );
    
}
void LineDrawing::deleteBufferAndArray()
{ glDeleteBuffers(1, &myVBO);
    glDeleteVertexArrays(1, &myVAO);
}

