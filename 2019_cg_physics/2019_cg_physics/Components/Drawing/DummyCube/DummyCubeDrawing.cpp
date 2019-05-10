//
//  DummyCube.cpp
//  2019_cg_physics
//
//  Created by Masud Mostafa on 09.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "DummyCubeDrawing.hpp"
#include "KeyboardManager.hpp"

/* standard includes */
#include<stdio.h>
#include<stdlib.h>

/* We use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* SOIL is used for loading (texture) images */
//#include <SOIL.h>
/* GLFW is used for creating and manipulating graphics windows */
#include<GLFW/glfw3.h>
/* GLNM is used for handling vector and matrix math */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLSL(src) "#version 330 core\n" #src
#define GLM_FORCE_RADIANS

const GLfloat SPEED = 0.03f;

void DummyCubeDrawing::Init()
{
    GLfloat points[] = {
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
    
    /* create and bind one Vertex Array Object */
    glGenVertexArrays(1, std::addressof(myVAO));
    glBindVertexArray(myVAO);
    
    glGenBuffers(1, std::addressof(myVBO));
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    /* copy the vertex data to it */
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    
    
    
    
    const char* vertexShaderSource = GLSL(
                                          in vec3 position;
                                          uniform mat4 proj;
                                          uniform mat4 view;
                                          uniform mat4 anim;
                                          void main() {
                                              gl_Position = proj * view * anim * vec4(position, 1.0);
                                          }
                                          );
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    /* check whether the vertex shader compiled without an error */
    //    if (!checkShaderCompileStatus(vertexShader)) {
    //        fprintf(stderr, "Vertex shader did not compile\n");
    //        exit(EXIT_FAILURE);
    //    }
    
    /* define and compile the fragment shader */
    const char* fragmentShaderSource = GLSL(
                                            out vec4 outColor;
                                            void main() {
                                                outColor = vec4(0.5f, 0.0f, 0.0f, 0.5f);
                                            }
                                            );
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    /* check whether the fragment shader compiled without an error */
    //    if (!checkShaderCompileStatus(fragmentShader)) {
    //        fprintf(stderr, "Fragment shader did not compile\n");
    //        exit(EXIT_FAILURE);
    //    }
    
    /* create a shader program by linking the vertex and fragment shader */
    shaderProgram  = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    
    /* check whether the shader program linked without an error */
    //    if (!checkShaderProgramLinkStatus(shaderProgram)) {
    //        fprintf(stderr, "Shader did not link\n");
    //        exit(EXIT_FAILURE);
    //    }
    
    /* define how the input is organized */
    const char* attributeName;
    attributeName = "position";
    GLint posAttrib = glGetAttribLocation(shaderProgram, attributeName);
    //    if (posAttrib == -1) {
    //        fprintf(stderr, "Error: could not bind attribute %s\n", attributeName);
    //        exit(EXIT_FAILURE);
    //    }
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), 0);
}

void DummyCubeDrawing::Draw()
{
    /* make the shader program active */
    glUseProgram(shaderProgram);
    
    /* define a view transformation */
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.5f, 3.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    
    /* define a  projection transformation */
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f/3.0f, 0.1f, 10.0f);
    
    /* define a transformation matrix for the animation */
    
    /* bind uniforms and pass data to the shader program */
    
    uniformName = "view";
    GLint uniformView = glGetUniformLocation(shaderProgram, uniformName);
    //    if (uniformView == -1) {
    //        fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
    //        exit(EXIT_FAILURE);
    //    }
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
    
    uniformName = "proj";
    GLint uniformProj = glGetUniformLocation(shaderProgram, "proj");
    //    if (uniformProj == -1) {
    //        fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
    //        exit(EXIT_FAILURE);
    //    }
    glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj));
    
    uniformName = "anim";
    GLint uniformAnim = glGetUniformLocation(shaderProgram, uniformName);
    //    if (uniformAnim == -1) {
    //        fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
    //        exit(EXIT_FAILURE);
    //    }
    
    dir = KeyboardManager::GetMoveDirection();
    
    if (dir == 0) {
        anim = glm::translate(anim, glm::vec3(SPEED, 0.0f, 0.0f));
        dir = -1;
    } else if (dir == 1) {
        anim = glm::translate(anim, glm::vec3(SPEED * (-1), 0.0f, 0.0f));
        dir = -1;
    } else if (dir == 2) {
        anim = glm::translate(anim, glm::vec3(0.0f, 0.0f, SPEED));
        dir = -1;
    } else if (dir == 3) {
        anim = glm::translate(anim, glm::vec3(0.0f, 0.0f, SPEED * (-1)));
        dir = -1;
    }
    glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));
    
    glBindVertexArray(myVAO);
    
    /* draw the VAO */
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
}

bool DummyCubeDrawing:: checkShaderCompileStatus(GLuint shaderID)
{
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = new char[length + 1];
        glGetShaderInfoLog(shaderID, length, &length, &log[0]);
        fprintf(stderr, "%s", log);
        return false;
    }
    return true;
}

bool DummyCubeDrawing:: checkShaderProgramLinkStatus(GLuint programID)
{
    {
        GLint status;
        glGetProgramiv(programID, GL_LINK_STATUS, &status);
        if(status == GL_FALSE) {
            GLint length;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
            GLchar* log = new char[length + 1];
            glGetProgramInfoLog(programID, length, &length, &log[0]);
            fprintf(stderr, "%s", log);
            return false;
        }
        return true;
    }
}
