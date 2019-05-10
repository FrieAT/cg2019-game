//
//  Camera.hpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 07.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLSL(src) "#version 330 core\n" #src
class Camera
{
public:
GLint organizeInputAttrib(GLint shaderProgram, const char* attributeName);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
bool checkShaderProgramLinkStatus(GLuint programID);
GLuint defineAndCompileFragmentShader();
bool checkShaderCompileStatus(GLuint shaderID);
GLint organizeInputUniform(GLint shaderProgram, const char* uniformName);
GLuint defineAndCompileVertexShader();
void initialize();
GLint shader;
GLint vertex;
GLint fragment ;
GLint uniformCam ;
GLint uniformView;
GLint uniformProj;
GLint uniformAnim;
GLint uniformMode;
GLint colAttrib ;
GLint shininessAttrib;
GLint posAttrib;
GLint normAttrib;
    glm::mat4 view ;
    glm::mat4 proj;
    
};

#include <stdio.h>

#endif /* Camera_hpp */
