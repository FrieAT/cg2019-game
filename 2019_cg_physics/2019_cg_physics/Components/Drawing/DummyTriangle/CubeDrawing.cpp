#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "CubeDrawing.hpp"
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


    if (dir == 0) {
        if ((curTrans[0] + SPEED) <= (STAGE_AREA_LENGTH_HALF - SPEED))
           curTrans[0] = curTrans[0] + SPEED;

//        dir = -1;
        } else if (dir == 1) {
        if ((curTrans[0] - SPEED) >= (-STAGE_AREA_LENGTH_HALF + SPEED))
            curTrans[0] = curTrans[0] - SPEED;

//        dir = -1;
    } else if (dir == 2) {
        if ((curTrans[2] + SPEED) <= (STAGE_AREA_WIDTH_HALF_BOTTOM - SPEED))
              curTrans[2] = curTrans[2] + SPEED;

//
//        dir = -1;
    } else if (dir == 3) {
        if ((curTrans[2] - SPEED) >= (-STAGE_AREA_WIDTH_HALF + SPEED))
            curTrans[2] = curTrans[2] - SPEED;

//
//        dir = -1;
    }

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
void StageDrawing::draw(GLint colAttrib, GLint uniformAnim, GLint uniformMode, GLint shininessAttrib)
{
    glBindVertexArray(vao);
    animPlayer = glm::mat4(1.0f);
    anim = glm::mat4(1.0f);
    animPlayer = glm::translate(anim, glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
    glUniformMatrix4fv(camera2.uniformAnim, 1, GL_FALSE, glm::value_ptr(animPlayer));
    //anim = glm::translate(anim, glm::vec3(curTrans[0],  curTrans[1], curTrans[2]));
    
    //   glUniformMatrix4fv(camera2.uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));
    
    
    
    glUniform1i(camera2.uniformMode, 0);
    glUniform1f(camera2.shininessAttrib, 300);
    
    
    glVertexAttrib3f(camera2.colAttrib, 1.0f, 0.0f, 0.0f);
    /* draw the VAO */
    glDrawArrays(GL_TRIANGLES, 0, 36);
////////////////////
    
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

