#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "DummyTriangleDrawing.hpp"
#include "KeyboardManager.hpp"
#include "Camera.hpp"
#include "StageDrawing.hpp"

Camera camera2;

StageDrawing stage;


const GLfloat STAGE_AREA_LENGTH_HALF = 2.0f;
const GLfloat STAGE_AREA_WIDTH_HALF = 1.0f;
void DummyTriangleDrawing::Draw()

{   GLfloat points[] = {
    -0.2f,-0.96f,-0.2f, /* bottom */
    0.2f,-0.96f,-0.2f,
    -0.2f,-0.96f, 0.2f,
    0.2f,-0.96f,-0.2f,
    0.2f,-0.96f, 0.2f,
    -0.2f,-0.96f, 0.2f,
    -0.2f,-0.25f,-0.2f, /* top */
    -0.2f,-0.25f, 0.2f,
    0.2f,-0.25f,-0.2f,
    0.2f,-0.25f,-0.2f,
    -0.2f,-0.25f, 0.2f,
    0.2f,-0.25f, 0.2f,
    -0.2f,-0.96f, 0.2f, /* font */
    0.2f,-0.96f, 0.2f,
    -0.2f,-0.25f, 0.2f,
    0.2f,-0.96f, 0.2f,
    0.2f,-0.25f, 0.2f,
    -0.2f,-0.25f, 0.2f,
    -0.2f,-0.96f,-0.2f, /* back */
    -0.2f,-0.25f,-0.2f,
    0.2f,-0.96f,-0.2f,
    0.2f,-0.96f,-0.2f,
    -0.2f,-0.25f,-0.2f,
    0.2f,-0.25f,-0.2f,
    -0.2f,-0.96f, 0.2f, /* left */
    -0.2f,-0.25f,-0.2f,
    -0.2f,-0.96f,-0.2f,
    -0.2f,-0.96f, 0.2f,
    -0.2f,-0.25f, 0.2f,
    -0.2f,-0.25f,-0.2f,
    0.2f,-0.96f, 0.2f, /* right */
    0.2f,-0.96f,-0.2f,
    0.2f,-0.25f,-0.2f,
    0.2f,-0.96f, 0.2f,
    0.2f,-0.25f,-0.2f,
    0.2f,-0.25f, 0.2f,
};

   
    camera2.initialize();
    /* create and bind one Vertex Array Object */
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);

    GLuint myVBO;
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    /* copy the vertex data to it */
    glBufferData(GL_ARRAY_BUFFER, sizeof(
                 points), points, GL_STATIC_DRAW);

 
    

    

   // const char* attributeName;

    glEnableVertexAttribArray(camera2.posAttrib);
    glVertexAttribPointer(camera2.posAttrib, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), 0);

//    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.5f, 3.0f),
//                                 glm::vec3(0.0f, 0.0f, 0.0f),
//                                 glm::vec3(0.0f, 1.0f, 0.0f));
//
//
//
//
//
//    uniformName = "view";
//    GLint uniformView = glGetUniformLocation(camera2.shader, uniformName);
//    if (uniformView == -1) {
//        fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
//        exit(EXIT_FAILURE);
//    }
//    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));


//    uniformName = "anim";
//    GLint uniformAnim = glGetUniformLocation(camera2.shader, uniformName);
//    if (uniformAnim == -1) {
//        fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
//        exit(EXIT_FAILURE);
//    }
//    glm::mat4 animPlayer = glm::mat4(1.0f);
    
    GLfloat curTrans [3] = { 0.0f, 0.0f, 0.0f };
  dir = KeyboardManager::GetMoveDirection();

//
//    if (dir == 0) {
//      anim = glm::translate(anim, glm::vec3(SPEED, 0.0f, 0.0f));
//        dir = -1;
//    } else if (dir == 1) {
//       anim = glm::translate(anim, glm::vec3(SPEED * (-1), 0.0f, 0.0f));
//        dir = -1;
//    } else if (dir == 2) {
//        anim = glm::translate(anim, glm::vec3(0.0f, 0.0f, SPEED));
//        dir = -1;
//    } else if (dir == 3) {
//        anim = glm::translate(anim, glm::vec3(0.0f, 0.0f, SPEED * (-1)));
//        dir = -1;
//    }
    if (dir == 0) {
       if ((curTrans[0] + SPEED) <= (STAGE_AREA_LENGTH_HALF - SPEED))
           curTrans[0] = curTrans[0] + SPEED;
           // anim = glm::translate(anim, glm::vec3(curTrans[0],  curTrans[1], curTrans[2]));
        dir = -1;
    } else if (dir == 1) {
        if ((curTrans[0] - SPEED) >= (-STAGE_AREA_LENGTH_HALF + SPEED))
            curTrans[0] = curTrans[0] - SPEED;
            //  anim = glm::translate(anim, glm::vec3(curTrans[0],curTrans[1],  curTrans[2]));
        dir = -1;
    } else if (dir == 2) {
        if ((curTrans[2] + SPEED) <= (STAGE_AREA_WIDTH_HALF - SPEED))
              curTrans[2] = curTrans[2] + SPEED;
            // anim = glm::translate(anim, glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
        
        dir = -1;
    } else if (dir == 3) {
        if ((curTrans[2] - SPEED) >= (-STAGE_AREA_WIDTH_HALF + SPEED))
            curTrans[2] = curTrans[2] - SPEED;
            // anim = glm::translate(anim, glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
   
        dir = -1;
    }
      anim = glm::translate(anim, glm::vec3(curTrans[0],  curTrans[1], curTrans[2]));
//    animPlayer = glm::translate(anim, glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
//    glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(animPlayer));
//    animPlayer = glm::translate(anim, glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
//   glUniformMatrix4fv(camera2.uniformAnim, 1, GL_FALSE, glm::value_ptr(animPlayer));
   glUniformMatrix4fv(camera2.uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));
//        animPlayer = glm::translate(glm::mat4(1.0f), glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
//    glUniformMatrix4fv(camera2.uniformAnim, 1, GL_FALSE, glm::value_ptr(animPlayer));
    glUniform1i(camera2.uniformMode, 0);
    glUniform1f(camera2.shininessAttrib, 300);

  
glVertexAttrib3f(camera2.colAttrib, 1.0f, 0.0f, 0.0f);
    /* draw the VAO */
    glDrawArrays(GL_TRIANGLES, 0, 36);

}




