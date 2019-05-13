//
//  StageDrawing.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 04.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "StageDrawing.hpp"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"
Camera camera1;
void StageDrawing::Draw()

{
    camera1.initialize();
    organize(camera1.posAttrib, camera1.normAttrib);
    draw(camera1.colAttrib, camera1.uniformAnim, camera1.uniformMode, camera1.shininessAttrib);
    deleteBufferAndArray();
   
}
void StageDrawing::organize(GLint posAttrib, GLint normAttrib)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), 0);
    
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_TRUE,
                          6 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vtxStage), vtxStage, GL_STATIC_DRAW);
}

void StageDrawing::draw(GLint colAttrib, GLint uniformAnim, GLint uniformMode, GLint shininessAttrib)
{
    glBindVertexArray(vao);
    
    glm::mat4 anim = glm::mat4(1.0f);
    glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));
    glUniform1i(uniformMode, 0);
    glUniform1f(shininessAttrib, 80);
    glVertexAttrib3f(colAttrib, 0.65f, 0.65f, 0.65f); // set constant color attribute
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glVertexAttrib3f(colAttrib, 0.0f, 0.0f, 0.0f); // set constant color attribute: black
    
    glDrawArrays(GL_TRIANGLE_STRIP, 36, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 40, 4);
}

void StageDrawing::deleteBufferAndArray()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

