//
//  CubeDrawing.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 12.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "CubeDrawing.hpp"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library


#include "KeyboardManager.hpp"
#include "Camera.hpp"
#include "StageDrawing.hpp"

Camera camera2;
StageDrawing stage;
void CubeDrawing::Draw()

{
    GLfloat points[] = {
        -0.2f,0.96f,-0.2f, /* bottom */
        0.2f,0.96f,-0.2f,
        -0.2f,0.96f, 0.2f,
        0.2f,0.96f,-0.2f,
        0.2f,0.96f, 0.2f,
        -0.2f,0.96f, 0.2f,
        -0.2f,0.25f,-0.2f, /* top */
        -0.2f,0.25f, 0.2f,
        0.2f,0.25f,-0.2f,
        0.2f,0.25f,-0.2f,
        -0.2f,0.25f, 0.2f,
        0.2f,0.25f, 0.2f,
        -0.2f,0.96f, 0.2f, /* font */
        0.2f,0.96f, 0.2f,
        -0.2f,0.25f, 0.2f,
        0.2f,0.96f, 0.2f,
        0.2f,0.25f, 0.2f,
        -0.2f,0.25f, 0.2f,
        -0.2f,0.96f,-0.2f, /* back */
        -0.2f,0.25f,-0.2f,
        0.2f,0.96f,-0.2f,
        0.2f,0.96f,-0.2f,
        -0.2f,0.25f,-0.2f,
        0.2f,0.25f,-0.2f,
        -0.2f,0.96f, 0.2f, /* left */
        -0.2f,0.25f,-0.2f,
        -0.2f,0.96f,-0.2f,
        -0.2f,0.96f, 0.2f,
        -0.2f,0.25f, 0.2f,
        -0.2f,0.25f,-0.2f,
        0.2f,0.96f, 0.2f, /* right */
        0.2f,0.96f,-0.2f,
        0.2f,0.25f,-0.2f,
        0.2f,0.96f, 0.2f,
        0.2f,0.25f,-0.2f,
        0.2f,0.25f, 0.2f,
    };
    
    
    camera2.initialize();
    organize(camera2.posAttrib);
    /* copy the vertex data to it */
    glBufferData(GL_ARRAY_BUFFER, sizeof(
                                         points), points, GL_STATIC_DRAW);
    
    
    dir = KeyboardManager::GetMoveDirection();
    
    movement();
    draw(camera2.colAttrib, camera2.uniformMode, camera2.shininessAttrib);
    deleteBufferAndArray();
}

/* generate and organize buffers */
void CubeDrawing::organize(GLint posAttrib)
{
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    
    glEnableVertexAttribArray(camera2.posAttrib);
    glVertexAttribPointer(camera2.posAttrib, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), 0);
    
    
}
void CubeDrawing::draw(GLint colAttrib, GLint uniformMode, GLint shininessAttrib)
{
    glBindVertexArray(myVAO);
    animPlayer = glm::translate(anim, glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
    glUniformMatrix4fv(camera2.uniformAnim, 1, GL_FALSE, glm::value_ptr(animPlayer));
 
    glUniform1i(uniformMode, 0);
    glUniform1f(shininessAttrib,300);
    
    
    glVertexAttrib3f(colAttrib, 1.0f, 0.0f, 0.0f);
    /* draw the VAO */
    glDrawArrays(GL_TRIANGLES, 0, 36);

}
void CubeDrawing::deleteBufferAndArray()
{
    glDeleteBuffers(1, &myVBO);
    glDeleteVertexArrays(1, &myVAO);
}
void CubeDrawing::movement(){
    
    if (dir == 0) {
        if ((curTrans[0] + SPEED) <= (STAGE_AREA_LENGTH_HALF - SPEED))
            curTrans[0] = curTrans[0] + SPEED;
        
    } else if (dir == 1) {
        if ((curTrans[0] - SPEED) >= (-STAGE_AREA_LENGTH_HALF + SPEED))
            curTrans[0] = curTrans[0] - SPEED;
      
    } else if (dir == 2) {
        if ((curTrans[2] + SPEED) <= (STAGE_AREA_WIDTH_HALF_BOTTOM - SPEED))
            curTrans[2] = curTrans[2] + SPEED;
        
    
    } else if (dir == 3) {
        if ((curTrans[2] - SPEED) >= (-STAGE_AREA_WIDTH_HALF + SPEED))
            curTrans[2] = curTrans[2] - SPEED;
        
    
    }
}
